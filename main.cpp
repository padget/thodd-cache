#include <thodd/cache/table.hpp>
#include <iostream>

using namespace thodd ;

int main() {
  cache::table tb = cache::define_table(
    "t_person", 
    cache::pk("id"), 
    cache::simple("nom"), 
    cache::simple("prenom"), 
    cache::simple("age")) ;

  std::cout << cache::insert(tb, "1", "robert", "dupont", "25") << std::endl ;
  std::cout << tb.name << std::endl ; 
  return EXIT_SUCCESS ;
}