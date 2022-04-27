namespace n_globals {
	inline int currently_selected = 0;
	inline int menu_selected = 0;
	inline int run_selected = -1;
}

struct colour_t {
	colour_t() = default;

	colour_t(int r, int g, int b, int a) :
		r(r),
		g(g),
		b(b),
		a(a)
	{}
 
	int r, g, b, a;
};

namespace n_vars {
	inline bool bool_var1;
	inline bool bool_var2;
	inline bool bool_var3;

	inline int int_var1;
	inline int int_var2;
	inline int int_var3;

	inline float float_var1;
	inline float float_var2;
	inline float float_var3;

	inline colour_t col_var1;
	inline colour_t col_var2;
	inline colour_t col_var3;
}