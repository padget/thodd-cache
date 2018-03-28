#ifndef __thodd_cache_table_hpp__
#  define __thodd_cache_table_hpp__

#  include <list>
#  include <vector>
#  include <map>
#  include <string>

namespace thodd::cache {
  using record = std::vector<std::string> ;

  struct table  {
    std::vector<std::string> header ;
    std::list<record> data ;
    std::map<std::string, record*> pk_index ; 
  } ;

  inline table define_table (auto && ... header_titles) {
    return {{header_titles...}} ;
  }

  inline int insert (table& t, auto && ... data) {
    auto && rec = record{data...} ;
    
    if (rec.size() == t.header.size() && t.pk_index.count(rec[0]) == 0) {
      t.data.push_back(record{data...}) ; // insertion dans la base 
      t.pk_index[t.data.back()[0]] = &t.data.back() ; // indexation
      return 1 ;
    }

    return 0 ;
  } 

  
}

#endif 