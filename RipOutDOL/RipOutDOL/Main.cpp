#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>

#define fseeko _fseeki64
#define ftello _ftelli64
#define atoll _atoi64
#define stat _stat64
#define fstat _fstat64
#define fileno _fileno
#define _tfopen_s   _wfopen_s

std::vector<uint8_t> m_bytes;

std::FILE* m_file;
enum
{
	DOL_NUM_TEXT = 7,
	DOL_NUM_DATA = 11
};

struct SDolHeader
{
	uint32_t textOffset[DOL_NUM_TEXT];
	uint32_t dataOffset[DOL_NUM_DATA];

	uint32_t textAddress[DOL_NUM_TEXT];
	uint32_t dataAddress[DOL_NUM_DATA];

	uint32_t textSize[DOL_NUM_TEXT];
	uint32_t dataSize[DOL_NUM_DATA];

	uint32_t bssAddress;
	uint32_t bssSize;
	uint32_t entryPoint;
};
SDolHeader m_dolheader;

std::vector<std::vector<uint8_t>> m_data_sections;
std::vector<std::vector<uint8_t>> m_text_sections;
bool m_good;
bool IsOpen() { return nullptr != m_file; }


inline uint32_t swap32(uint32_t data)
{
	return _byteswap_ulong(data);
}

bool Initialize(const std::vector<uint8_t>& buffer)
{
	memcpy(&m_dolheader, buffer.data(), sizeof(SDolHeader));

	// swap memory
	uint32_t* p = (uint32_t*)&m_dolheader;
	for (size_t i = 0; i < (sizeof(SDolHeader) / sizeof(uint32_t)); i++)
		p[i] = swap32(p[i]);

	const uint32_t HID4_pattern = swap32(0x7c13fba6);
	const uint32_t HID4_mask = swap32(0xfc1fffff);

	bool m_is_wii = false;

	m_text_sections.reserve(DOL_NUM_TEXT);
	for (int i = 0; i < DOL_NUM_TEXT; ++i)
	{
		if (m_dolheader.textSize[i] != 0)
		{
			if (buffer.size() < m_dolheader.textOffset[i] + m_dolheader.textSize[i])
				return false;

			const uint8_t* text_start = &buffer[m_dolheader.textOffset[i]];
			m_text_sections.emplace_back(text_start, &text_start[m_dolheader.textSize[i]]);

			for (unsigned int j = 0; !m_is_wii && j < (m_dolheader.textSize[i] / sizeof(uint32_t)); ++j)
			{
				uint32_t word = ((uint32_t*)text_start)[j];
				if ((word & HID4_mask) == HID4_pattern)
					m_is_wii = true;
			}
		}
		else
		{
			// Make sure that m_text_sections indexes match header indexes
			m_text_sections.emplace_back();
		}
	}

	m_data_sections.reserve(DOL_NUM_DATA);
	for (int i = 0; i < DOL_NUM_DATA; ++i)
	{
		if (m_dolheader.dataSize[i] != 0)
		{
			if (buffer.size() < m_dolheader.dataOffset[i] + m_dolheader.dataSize[i])
				return false;

			const uint8_t* data_start = &buffer[m_dolheader.dataOffset[i]];
			m_data_sections.emplace_back(data_start, &data_start[m_dolheader.dataSize[i]]);
		}
		else
		{
			// Make sure that m_data_sections indexes match header indexes
			m_data_sections.emplace_back();
		}
	}

	return true;
}


template <typename T>
bool ReadArray(T* elements, size_t count, size_t* num_read = nullptr)
{
	size_t read_count = 0;
	if (!IsOpen() || count != (read_count = std::fread(elements, sizeof(T), count, m_file)))
		m_good = false;

	if (num_read)
		*num_read = read_count;

	return m_good;
}

bool ReadBytes(void* data, size_t length)
{
	return ReadArray(reinterpret_cast<char*>(data), length);
}

uint64_t GetSize(FILE* f)
{
	// can't use off_t here because it can be 32-bit
	uint64_t pos = ftello(f);
	if (fseeko(f, 0, SEEK_END) != 0)
	{
	}

	uint64_t size = ftello(f);
	if ((size != pos) && (fseeko(f, pos, SEEK_SET) != 0))
	{
	}

	return size;
}

void PrintText()
{
	std::ofstream DataOutputFile;
	DataOutputFile.open("C:\\users\\Darren\\Desktop\\SoAData.txt", std::ios::trunc);
	// load all data sections
	for (size_t i = 0; i < m_data_sections.size(); ++i)
		if (!m_data_sections[i].empty())
		{
			bool enterANewLine = false;
			DataOutputFile << "\nData Section: " << i << std::endl;
			for (int mySize = 0; mySize < m_data_sections[i].size(); mySize++)
			{
				char characterToPrint = (m_data_sections[i].data()[mySize]);

				/*if (characterToPrint == '\0')
				{
					enterANewLine = true;
				}
				else
				{
					if (characterToPrint >= 32 && characterToPrint <= 122)
					{
						if (enterANewLine)
						{
							DataOutputFile << std::endl;
						}
						DataOutputFile << characterToPrint;
						enterANewLine = false;
					}
				}*/

				/*			if (characterToPrint == '\0' || characterToPrint >= 32)
							{
								if (characterToPrint == '\0')
								{
									DataOutputFile << '\n';
								}
								else
								{*/
				DataOutputFile << characterToPrint;
				//}
			//}
			}
		}
	DataOutputFile.close();
}

int main()
{
	const std::string fileName("SoaDOL.dol");
	errno_t error = fopen_s(&m_file, fileName.c_str(), "rb");

	m_bytes.resize(GetSize(m_file));
	ReadBytes(m_bytes.data(), m_bytes.size());
	Initialize(m_bytes);

	std::fclose(m_file);

	PrintText();
}