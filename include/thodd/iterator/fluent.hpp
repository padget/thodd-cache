#ifndef __thodd_iterator_fluent_hpp__
#  define __thodd_iterator_fluent_hpp__

#  include <thodd/iterator/iterator.hpp>

namespace thodd {

  template <typename iterator_t>
  struct stream ;

  template <typename iterator_t>
  stream<iterator_t> make_stream (iterator_t const & it) {
    return {it} ;
  }

  auto as_stream(auto const & container) {
    return make_stream(thodd::make_range(container)) ;
  }

  template <typename ... iterator_t>
  struct stream_n ;

  template <typename ... iterator_t>
  stream_n<iterator_t...> make_stream_n (iterator_t const & ... its) {
    return {thodd::join(its...)} ;
  }

  template <typename iterator_t>
  struct stream {
    iterator_t it ;

    auto map (auto const & mapper) {
      return make_stream(thodd::map(it, mapper)) ;
    }

    auto filter (auto const & predicate) {
      return make_stream(thodd::filter(it, predicate)) ;
    }

    auto collect (auto const & collector) {
      return thodd::collect(it, collector) ;
    }

    auto reduce (auto const & reducer, auto const & init) {
      return thodd::reduce(it, reducer, init) ;
    }

    void foreach (auto const & on_each) {
      thodd::foreach(it, on_each) ;
    }

    auto join (auto const & ... its) {
      return make_stream_n(it, its...) ;
    }
  } ;

  template <typename ... iterator_t>
  struct stream_n {
    join_iterator<iterator_t...> jit ;

    auto map_n(auto const & mapper_n) {
      return make_stream(thodd::map_n(jit, mapper_n)) ;
    }
    
    auto filter_n(auto const & predicate_n) {
      return make_stream(thodd::filter_n(jit, predicate_n)) ;
    }

    auto reduce_n (auto const & reducer_n, auto const & init) {
      return thodd::reduce_n(jit, reducer_n, init) ;
    }

    void foreach_n (auto const & on_each_n) {
      thodd::foreach_n(jit, on_each_n) ;
    }
  } ;

  
}

#endif