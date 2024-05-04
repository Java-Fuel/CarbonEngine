#pragma once

#include "CarbonLogger.h"

/*
 * This file contains all structs, classes, and interfaces required to
 * implement a platform event handler.
 */

struct PlatformEventArgs
{
  int first;
  int second;
};

class IPlatformEventHandler
{
  /* Variables */

  /* Methods  */
public:
  virtual void publish(PlatformEventArgs* args) {};


private:
  virtual void m_exec(PlatformEventArgs* args) {};
};

template<typename T>
class PlatformEventHandler : public IPlatformEventHandler
{
  /* Variables */
public:
  typedef void (T::* PlatformEventCallback)(PlatformEventArgs*);

private:
  T* instance;
  PlatformEventCallback callback;

  /* Methods */
public:
  PlatformEventHandler() = default;
  PlatformEventHandler(T* instance, PlatformEventCallback callback);
  void publish(PlatformEventArgs* args);

private:
  void m_exec(PlatformEventArgs* args);
};

#include "PlatformEventHandler.inl"