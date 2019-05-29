// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Common/CommonTypes.h"
#include "Core/IOS/ES/Formats.h"
#include "DiscIO/Volume.h"

namespace DiscIO
{
class BlobReader;
enum class BlobType;
enum class Country;
class FileSystem;
enum class Language;
enum class Region;
enum class Platform;

class VolumeWAD : public Volume
{
public:
  VolumeWAD(std::unique_ptr<BlobReader> reader);
  ~VolumeWAD();
  bool Read(u64 offset, u64 length, u8* buffer,
            const Partition& partition = PARTITION_NONE) const override;
  const FileSystem* GetFileSystem(const Partition& partition = PARTITION_NONE) const override;
  std::optional<u64> GetTitleID(const Partition& partition = PARTITION_NONE) const override;
  const IOS::ES::TicketReader&
  GetTicket(const Partition& partition = PARTITION_NONE) const override;
  const IOS::ES::TMDReader& GetTMD(const Partition& partition = PARTITION_NONE) const override;
  const std::vector<u8>&
  GetCertificateChain(const Partition& partition = PARTITION_NONE) const override;
  std::vector<u64> GetContentOffsets() const override;
  std::string GetGameID(const Partition& partition = PARTITION_NONE) const override;
  std::string GetGameTDBID(const Partition& partition = PARTITION_NONE) const override;
  std::string GetMakerID(const Partition& partition = PARTITION_NONE) const override;
  std::optional<u16> GetRevision(const Partition& partition = PARTITION_NONE) const override;
  std::string GetInternalName(const Partition& partition = PARTITION_NONE) const override
  {
    return "";
  }
  std::map<Language, std::string> GetLongNames() const override;
  std::vector<u32> GetBanner(u32* width, u32* height) const override;
  std::string GetApploaderDate(const Partition& partition = PARTITION_NONE) const override
  {
    return "";
  }
  Platform GetVolumeType() const override;
  Region GetRegion() const override;
  Country GetCountry(const Partition& partition = PARTITION_NONE) const override;

  BlobType GetBlobType() const override;
  u64 GetSize() const override;
  bool IsSizeAccurate() const override;
  u64 GetRawSize() const override;

private:
  std::unique_ptr<BlobReader> m_reader;
  IOS::ES::TicketReader m_ticket;
  IOS::ES::TMDReader m_tmd;
  std::vector<u8> m_cert_chain;
  u32 m_cert_chain_offset = 0;
  u32 m_ticket_offset = 0;
  u32 m_tmd_offset = 0;
  u32 m_data_offset = 0;
  u32 m_opening_bnr_offset = 0;
  u32 m_hdr_size = 0;
  u32 m_cert_chain_size = 0;
  u32 m_ticket_size = 0;
  u32 m_tmd_size = 0;
  u32 m_data_size = 0;
};

}  // namespace DiscIO