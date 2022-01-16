// Copyright 2020 Your Name <your_email>

#include <header.hpp>

Json::Json(const std::string& name_) : name(name_) {}
json Json::mem() const{
  return memory;
}
void Json::read(){
  try{
    std::ifstream in(name);
    in >> memory;
  }catch (const std::exception& exc) {
    std::cerr << exc.what() << '\n';
  }
}

suggest::suggest(){
  suggestion = {};
}
void suggest::Update(json j){
  std::sort(j.begin(), j.end(), [](const json& a, const json& b) -> bool {
    return a.at("cost") < b.at("cost");
  });
  suggestion = j;
}
json suggest::do_suggest(const std::string& s) {
  json filee;
  for (size_t i = 0, m = 0; i < suggestion.size(); ++i) {
    if (s == suggestion[i].at("id")) {
      json Json;
      Json["text"] = suggestion[i].at("name");
      Json["position"] = m++;
      filee["suggestions"].push_back(Json);
    }
  }
  return filee;
}