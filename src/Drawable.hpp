#pragma once

// Type erased class for types that have an overloade draw(type t) function

#include <memory>

// Implementation classes

struct Storage
{
   virtual void docall() = 0;
};

template <typename T>
struct StorageImpl : Storage
{
   StorageImpl(T t) : m_t{ std::move(t) }
   {}

   void docall() override {
      draw(m_t);
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

   void draw() { m_storage->docall(); }

   friend void draw(const Drawable& d) { d.m_storage->docall(); }

private:
   std::unique_ptr<Storage> m_storage;
};


