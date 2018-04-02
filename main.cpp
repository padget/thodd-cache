#include <thodd/cache/table/table-functions.hpp>
#include <iostream>

using namespace thodd ;

void print_record (cache::record const & rec) {
  for (auto const & fld : rec) 
    std::cout << fld << ',' ;

  std::cout << "\n" ; 
}

void print_table (cache::table const & table) {
  std::cout << "----------------- " << table.name << " ----------------\n" ; 
  
  for (auto const & head : table.header)
    std::cout << std::get<1>(head) << ',' ;

  std::cout << '\n' ;
  
  for (auto const & rec : table.data) 
    print_record(rec) ;

  std::cout << "\n\n" ;
  std::cout << "index --- \n\n" ;
  
  for (auto const & index_entry : table.pk_index)
    std::cout << index_entry.first << ":" << index_entry.second << "\n" ;
}

int main() {
  cache::table tb = cache::define_table(
    "t_person", 
    cache::pk("id"), 
    cache::simple("nom"), 
    cache::simple("prenom"), 
    cache::simple("age")) ;

  cache::insert(tb, cache::record{"1", "robert", "dupont", "25"}, 
                    cache::record{"2", "robert", "dupont", "25"}, 
                    cache::record{"3", "robert", "dupont", "25"},
                    cache::record{"4", "robert", "dupont", "25"}) ;
                    
  print_table(tb) ;

  return EXIT_SUCCESS ;
}