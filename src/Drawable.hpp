#pragma once

// Type erased class for types that have an overloade draw(type t) function

#include <memory>

// Implementation classes

struct Storage
{
   virtual void doDraw() = 0;
   virtual void doUpdate() = 0;
};

template <typename T>
struct StorageImpl : Storage
{
   StorageImpl(T t) : m_t{ std::move(t) }
   {}

   void doDraw() override 
   {
      draw(m_t);
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

   void draw() { m_storage->doDraw(); }

   void update() { m_storage->doUpdate(); }

   friend void draw(const Drawable& d) { d.m_storage->doDraw(); }
   
   friend void update(const Drawable& d) { d.m_storage->doUpdate(); }

private:
   std::unique_ptr<Storage> m_storage;
};


