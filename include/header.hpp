// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <nlohmann/json.hpp>
#include <string>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
using json = nlohmann::json;

class Json {
 public:
  explicit Json(const std::string& name_);
  json mem() const;
  void read();

 private:
  std::string name;
  json memory;
};


class suggest {
 public:
  suggest();
  void Update(json JSON);
  json do_suggest(const std::string& str);

 private:
  json suggestion;
};

#endif // INCLUDE_HEADER_HPP_
