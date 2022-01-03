#pragma once

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

// begin DTO
#include OATPP_CODEGEN_BEGIN(DTO)

class MessageDto : public oatpp::DTO {
  DTO_INIT(MessageDto, DTO)
  DTO_FIELD(Int32, StatusCode);
  DTO_FIELD(String, Msg);
};

// TODO(bayec): add more DTOs here

// end DTO
#include OATPP_CODEGEN_END(DTO)
