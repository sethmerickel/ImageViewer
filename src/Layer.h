#pragma once

class ShaderProgram;

class Layer
{
public:
   Layer() = default;
   virtual ~Layer() = 0;
   virtual void draw() = 0;
   virtual void reload() = 0;


private:
   // Not copyable
   Layer(const Layer& layer) = delete;
   Layer& operator=(const Layer& layer) = delete;
};

