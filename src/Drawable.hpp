#pragma once
// Type erased class for drawable type, types to be rendered to the view. To make a 
// type drawable implement 2 free functions (possibly friends)
//    1) void draw(<your type>&)  
//    2) void update(<your type>&)


#include <memory>

#include "ShaderProgram.h"

// Implementation classes

struct Storage
{
   virtual void doDraw(ShaderProgram& sp) = 0;
   virtual void doUpdate() = 0;
};

template <typename T>
struct StorageImpl : Storage
{
   StorageImpl(T t) : m_t{ std::move(t) }
   {}

   void doDraw(ShaderProgram& sp) override 
   {
      draw(m_t, sp);
   }

   void doUpdate() override 
   {
      update(m_t);
   }

   T m_t;
};

// Public interface

class Drawable
{
public:

   template <typename T>
   Drawable(T t) 
      : m_storage{ std::make_unique<StorageImpl<T>>(std::move(t)) }
   {}

   void 
   draw(ShaderProgram& sp)
   {
      m_storage->doDraw(sp); 
   }

   void update() { m_storage->doUpdate(); }

   friend void 
   draw(const Drawable& d, ShaderProgram& sp) 
   {
      d.m_storage->doDraw(sp);
   }
   
   friend void
   update(const Drawable& d)
   {
      d.m_storage->doUpdate(); 
   }

private:
   std::unique_ptr<Storage> m_storage;
};


