#ifndef LUL_TOOLS
#define LUL_TOOLS

// OOP helper methods
#define call(item, method) item->method(item)
#define apply(item, method, args...) item->method(item, args)
#define add_method(target, name) target->name = &name

// MIN and MAX
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))



#endif 
