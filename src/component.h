#pragma once

#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"

/**
 *  创建和持有应用程序组件的类，并在oatpp::base::Environment中注册组件
 *  组件初始化的顺序是由上至下的
 */
class Component {
 public:
  /**
   *  创建监听端口的ConnectionProvider组件
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, server_connection_provider)
  ([] {
    return oatpp::network::tcp::server::ConnectionProvider::createShared(
        {"localhost", 60080, oatpp::network::Address::IP_4});
  }());

  /**
   *  创建Router组件
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, http_router)
  ([] { return oatpp::web::server::HttpRouter::createShared(); }());

  /**
   *  创建ConnectionHandler组件，该组件使用Router组件来路由请求
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, server_connection_handler)
  ([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    return oatpp::web::server::HttpConnectionHandler::createShared(router);
  }());

  /**
   *  创建ObjectMapper组件来序列化/反序列化Contoller的API中的DTOs
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, api_object_mapper)
  ([] { return oatpp::parser::json::mapping::ObjectMapper::createShared(); }());
};
