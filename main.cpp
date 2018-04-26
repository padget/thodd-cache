#include <thodd/cache/table/table-functions.hpp>

#include <thodd/iterator/iterator.hpp>
#include <thodd/iterator/fluent.hpp>

#include <iostream>
#include <typeinfo> 

using namespace thodd ;

void print_record (cache::record const & rec) {
  for (auto const & fld : rec) 
    std::cout << fld << ',' ;

  std::cout << "\n" ; 
}

void print_column (cache::column const & col) {
  switch(cache::get_type(col)) {
    case cache::column_type::primary_key : std::cout << "pk    " ; break ;
    case cache::column_type::foreign_key : std::cout << "fk    " ; break ;
    case cache::column_type::simple      : std::cout << "simple" ; break ; 
  }

  std::cout << ' ' ;
  std::cout << cache::get_name(col) ;
  std::cout << '\n' ;  
}

void print_table (cache::table const & table) {
  std::cout << "----------------- " 
            << table.name 
            << " ----------------\n" ; 
  
  for (auto const & col : table.header) {
    print_column(col) ;
  }

  std::cout << '\n' ;
  
  for (auto const & rec : table.data) 
    print_record(rec) ;

  std::cout << "\n\n" ;
  std::cout << "index --- \n\n" ;
  
  for (auto const & index_entry : table.pk_index)
    std::cout << index_entry.first << ":" << index_entry.second << "\n" ;
}


int main () {
  constexpr auto id = [] (std::string const & data) {
    return data ;
  } ;

  cache::table tb = cache::define_table(
    "t_person", 
    cache::pk("id", cache::valid(), id), 
    cache::simple("nom", cache::format("bill.*"), [] (auto const & data) {return data + "prout" ;}), 
    cache::simple("prenom", cache::valid(), id), 
    cache::simple("age", cache::valid(), id)) ;

  cache::insert(tb, cache::record{"1", "robert"  , "dupont", "25"}, 
                    cache::record{"2", "robert"  , "dupont", "25"}, 
                    cache::record{"3", "billkill", "dupont", "25"},
                    cache::record{"4", "robert"  , "dupont", "25"}) ;
                    
  print_table(tb) ;

  return EXIT_SUCCESS ;
}