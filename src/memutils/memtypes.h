// mutable resource ownership
// responsible for free()
//
// use on:
// - Return values of constructors/factories
// - Function parameters when transferring ownership IN
// - Struct fields that own resources
// - Local variables that allocate resources
#define OWNER(T) T*

// borrows resource for read
// not responsible for free()
//
// use on:
// - Function parameters for read-only access
// - Return values from getters that don't transfer ownership
// - Local references to existing resources
// - Const member function parameters
#define BORROW(T) const T*

// borrows resource for read and write
// not responsible for free()
// default type for fun parameter
//
// use on:
// - Function parameters that modify but don't take ownership
// - Iterator/reference parameters
// - Output parameters that populate existing resources
// - Mutable member function parameters
#define MUT_BORROW(T) T*

// weak pointer to const resource
// does not guarantee non-null
// not responsible for free()
//
// use on:
// - Parent references in tree structures (child → parent)
// - Cache entries that may be evicted
// - Observers/subscribers that don't own subject
// - Back-references in graphs
// - Callback context pointers
#define WEAK(T) const T*

// weak pointer to mutable resource
// does not guarantee non-null
// not responsible for free()
//
// use on:
// - Mutable parent references (when child may modify parent)
// - Mutable cache entries
// - Iterators over collections that may be modified
// - Non-const observer patterns
// - Contexts with mutation privileges
#define MUT_WEAK(T) T*

