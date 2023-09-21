/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.robotraconteur;

public class WrappedNamedMultiDimArrayMemoryDirector {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected WrappedNamedMultiDimArrayMemoryDirector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(WrappedNamedMultiDimArrayMemoryDirector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        RobotRaconteurJavaJNI.delete_WrappedNamedMultiDimArrayMemoryDirector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() {
    swigCMemOwn = false;
    RobotRaconteurJavaJNI.WrappedNamedMultiDimArrayMemoryDirector_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    RobotRaconteurJavaJNI.WrappedNamedMultiDimArrayMemoryDirector_change_ownership(this, swigCPtr, true);
  }

  public vector_uint64_t dimensions() {
    return new vector_uint64_t(RobotRaconteurJavaJNI.WrappedNamedMultiDimArrayMemoryDirector_dimensions(swigCPtr, this), true);
  }

  public long dimCount() {
    return RobotRaconteurJavaJNI.WrappedNamedMultiDimArrayMemoryDirector_dimCount(swigCPtr, this);
  }

  public MessageElementNestedElementList read(vector_uint64_t memorypos, vector_uint64_t bufferpos, vector_uint64_t count) {
    long cPtr = RobotRaconteurJavaJNI.WrappedNamedMultiDimArrayMemoryDirector_read(swigCPtr, this, vector_uint64_t.getCPtr(memorypos), memorypos, vector_uint64_t.getCPtr(bufferpos), bufferpos, vector_uint64_t.getCPtr(count), count);
    return (cPtr == 0) ? null : new MessageElementNestedElementList(cPtr, true);
  }

  public void write(vector_uint64_t memorypos, MessageElementNestedElementList buffer, vector_uint64_t bufferpos, vector_uint64_t count) {
    RobotRaconteurJavaJNI.WrappedNamedMultiDimArrayMemoryDirector_write(swigCPtr, this, vector_uint64_t.getCPtr(memorypos), memorypos, MessageElementNestedElementList.getCPtr(buffer), buffer, vector_uint64_t.getCPtr(bufferpos), bufferpos, vector_uint64_t.getCPtr(count), count);
  }

  public void setObjectheapid(int value) {
    RobotRaconteurJavaJNI.WrappedNamedMultiDimArrayMemoryDirector_objectheapid_set(swigCPtr, this, value);
  }

  public int getObjectheapid() {
    return RobotRaconteurJavaJNI.WrappedNamedMultiDimArrayMemoryDirector_objectheapid_get(swigCPtr, this);
  }

  public WrappedNamedMultiDimArrayMemoryDirector() {
    this(RobotRaconteurJavaJNI.new_WrappedNamedMultiDimArrayMemoryDirector(), true);
    RobotRaconteurJavaJNI.WrappedNamedMultiDimArrayMemoryDirector_director_connect(this, swigCPtr, true, true);
  }

}
