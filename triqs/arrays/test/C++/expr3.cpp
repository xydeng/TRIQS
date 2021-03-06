
/*******************************************************************************
 *
 * TRIQS: a Toolbox for Research in Interacting Quantum Systems
 *
 * Copyright (C) 2011 by O. Parcollet
 *
 * TRIQS is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * TRIQS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * TRIQS. If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include "./python_stuff.hpp"
#include "./src/array.hpp"
#include <iostream>
using namespace std;
using namespace triqs::arrays;
using namespace indexmaps;
using namespace storages;

#include "./src/array.hpp"
#include "./src/matrix.hpp"
//#include "./src/vector.hpp"

#include "./src/expressions/array_algebra.hpp"
#include <boost/type_traits/is_convertible.hpp>
#include <boost/proto/debug.hpp>
 
namespace ExpressionTools { 

  /** 
   * Map any callable object to an array expression, elementwise
   */
  namespace details { 
   template<typename Obj, typename Expr> 
    struct map_impl : Tag::expression, Tag::array_algebra_expression_terminal {
     typedef typename Expr::value_type   value_type;
     typedef typename Expr::domain_type  domain_type;
     Expr const & a;Obj const & obj;std::string name;
     map_impl( Obj const & obj_, Expr const & a_,std::string const & name_):a(a_),obj(obj_),name(name_){}
     domain_type domain() const { return a.domain();}
     value_type operator[] (typename Expr::domain_type::index_value_type const & key) const { return obj(a [key]); }
    };
   template<typename Obj, typename Expr> 
    std::ostream & operator<<(std::ostream & out, map_impl<Obj,Expr> const & x){ return out<<x.name<<"("<<x.a<<")";}
  }

  template<typename Obj, typename Expr> 
   details::map_impl<Obj,Expr> map_expr (Obj const & obj, Expr const & x,std::string const & name="Unknown") { 
    return details::map_impl<Obj,Expr>(obj,x,name);
   }

  /** 
   * Transpose any array expression
   */
  namespace details { 

   template<typename Expr> 
    struct transpose_impl : Tag::expression, Tag::array_algebra_expression_terminal {
     typedef typename Expr::value_type   value_type;
     typedef typename Expr::domain_type  domain_type;
     Expr const & a;
     transpose_impl( Expr const & a_):a(a_){}
     domain_type domain() const { return domain_type(mini_vector<size_t,2>(a.domain().lengths()[1], a.domain().lengths()[0])); } 
     typedef typename Expr::domain_type::index_value_type K; 
     value_type operator[] (K const & key) const { return a [ K( key[1], key[0]) ]; }
    };

   template<typename T> 
    std::ostream & operator<<(std::ostream & out, transpose_impl<T> const & x){ return out<<"Transpose("<<x.a<<")";}


   template<class Expr, template <class Expr2> class Transfo>
    struct transfo_impl : Transfo<Expr>,  Tag::expression, Tag::array_algebra_expression_terminal { 
     Expr const & a; transfo_impl( Expr const & a_):a(a_){}
     typedef Transfo<Expr> T;
     typename T::domain_type domain() const { return T::domain(a);}
     typename T::value_type operator[] (typename T::domain_type::index_value_type const & key) const { return T::eval(a,key); }
    };

   template<class Expr, template <class Expr2> class Transfo>
    std::ostream & operator<<(std::ostream & out, transfo_impl<Expr,Transfo> const & x){ return out<<Transfo<Expr>::name()<<"("<<x.a<<")";}

  }

  //template<typename Expr> details::transpose_impl<Expr> Transpose (Expr const & x) { return details::transpose_impl<Expr>(x);}

  template<typename Expr> 
   struct transpose_  {
    static_assert(  has_immutable_array_interface<Expr>::value, "transpose_ : the type of the template argument is incorrect, it does not support ArrayImmutableInterface");
    // static checks here on Expr
    static std::string name() { return "Transpose";}
    typedef typename Expr::value_type   value_type;
    typedef typename Expr::domain_type  domain_type;
    static domain_type domain(Expr const & a) { return domain_type(mini_vector<size_t,2>(a.domain().lengths()[1], a.domain().lengths()[0])); } 
    static value_type eval (Expr const & a, typename domain_type::index_value_type const & key) { 
     	return a [ typename domain_type::index_value_type ( key[1], key[0]) ]; 
    }
   };


#define TRIQS_ARRAYS_NAME_APPLY_ARRAY_FUNCTION(Name, ArrayFunction)\
  namespace result_of { template<typename Expr> struct Name { typedef details::transfo_impl<Expr,ArrayFunction> type; }; }\
  template<typename Expr> typename result_of::Name<Expr>::type Name (Expr const & x) { return typename result_of::Name<Expr>::type (x);}\

  TRIQS_ARRAYS_NAME_APPLY_ARRAY_FUNCTION (Transpose, transpose_)

 }

using namespace ExpressionTools;

int sqr(int x) { return x*x;}

//DEFINE_ARRAY_FUNCTION1( Transpose, transpose_impl);

int main(int argc, char **argv) {

 init_python_stuff(argc,argv);

 {
  array<int,1> A(3),B(3),C(3);
  array<double,1> F(3);  
  for (int i =0; i<3; ++i) {
   A(i) = i;
   B(i) = 1;
   C(i) =  10 *i;
   F(i) = 2.5 + i;
  }

  cout<<" A = "<<A<<endl;
  cout<<" B = "<<B<<endl;
  cout<<" C = "<<C<<endl;
  cout<<" F = "<<F<<endl;

  array<double,1> V1(3), V2(3);

  //proto::display_expr(A);
  // cout<< (A+B) <<endl;
  // cout<<V1 + V2 <<endl;

  // type computation 
  expressions::print_structure(cout, A+ F);
  cout<<" A + F = "<< array<double,1>(A+F)<<endl;

 }

 {
  array<long,2> A (2,2), B(2,2),C(2,2);
  for (int i =0; i<2; ++i)
   for (int j=0; j<2; ++j) 
   { A(i,j) = 10*i+ j;B(i,j) = i+ 2*j;}
  cout<<" A = "<<A<<endl;
  cout<<" B = "<<B<<endl;

  matrix<double> M1(2,2);
  //cout<<M1 + A<<endl; // this should NOT COMPILE

  cout<< (A+2*B) <<endl;
  cout<<"-------"<<endl;

  cout<< (A+2*B).domain()<<endl;
  cout<<"----EVAL ---"<<endl;

  C= A + 2*B;
  cout<<" C = "<<C<<endl;

  C= std::plus<array<long,2> >()(A,B);
  cout<<" C = "<<C<<endl;

  // array multiplication 
  C = A* B;
  cout<<" C = A*B "<<C<<endl;

  // array division
  array<double,2> Af (2,2), Bf(2,2),Cf(2,2);
  Af = A; Bf = B; Bf(0,0) = 1;
  cout<<" Af = "<<Af<<endl;
  cout<<" Bf = "<<Bf<<endl;
  Cf = Af / Bf;
  cout<<" Cf = Af/Bf "<<Cf<<endl;

  C = A + Transpose(B);
  cout<<" C = "<<C<<endl;

  C = A + Transpose(B + B);
  cout<<" C = "<<C<<endl;

  C = Transpose(B);
  cout<<" C = "<<C<<endl;

  cout<<" t A"<<Transpose(A)<<endl;

  array<double,2> F( 0.5 * A);
  cout << " 0.5 * A = "<<F <<endl;

  // non square
  array<long,2> R(2,3),Rt(3,2);
  for (int i =0; i<2; ++i)
   for (int j=0; j<3; ++j) 
   { R(i,j) = 10*i+ j;}

  //cout<<" R = "<< 1 + R<<endl;
  cout<<" R = "<< array<long,2>(Transpose(R)) <<endl;

  C =  map_expr(&sqr,A);
  cout<<" C = "<< map_expr(&sqr,A,"SQR")<<" = "<<C<<endl;

 }
 return 0;
}
