/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.robotraconteur;

public class WrappedGeneratorClient {
  private transient long swigCPtr;
  private transient boolean swigCMemOwn;

  protected WrappedGeneratorClient(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(WrappedGeneratorClient obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void swigSetCMemOwn(boolean own) {
    swigCMemOwn = own;
  }

  @SuppressWarnings({"deprecation", "removal"})
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        RobotRaconteurJavaJNI.delete_WrappedGeneratorClient(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public MessageElement next(MessageElement v) {
    long cPtr = RobotRaconteurJavaJNI.WrappedGeneratorClient_next(swigCPtr, this, MessageElement.getCPtr(v), v);
    return (cPtr == 0) ? null : new MessageElement(cPtr, true);
  }

  public WrappedGeneratorClient_TryGetNextResult tryNext(MessageElement v) {
    return new WrappedGeneratorClient_TryGetNextResult(RobotRaconteurJavaJNI.WrappedGeneratorClient_tryNext(swigCPtr, this, MessageElement.getCPtr(v), v), true);
  }

  public void asyncNext(MessageElement v, int timeout, AsyncRequestDirector handler, int id) {
    RobotRaconteurJavaJNI.WrappedGeneratorClient_asyncNext(swigCPtr, this, MessageElement.getCPtr(v), v, timeout, AsyncRequestDirector.getCPtr(handler), handler, id);
  }

  public void abort() {
    RobotRaconteurJavaJNI.WrappedGeneratorClient_abort(swigCPtr, this);
  }

  public void asyncAbort(int timeout, AsyncVoidReturnDirector handler, int id) {
    RobotRaconteurJavaJNI.WrappedGeneratorClient_asyncAbort(swigCPtr, this, timeout, AsyncVoidReturnDirector.getCPtr(handler), handler, id);
  }

  public void close() {
    RobotRaconteurJavaJNI.WrappedGeneratorClient_close(swigCPtr, this);
  }

  public void asyncClose(int timeout, AsyncVoidReturnDirector handler, int id) {
    RobotRaconteurJavaJNI.WrappedGeneratorClient_asyncClose(swigCPtr, this, timeout, AsyncVoidReturnDirector.getCPtr(handler), handler, id);
  }

  public vectorptr_messageelement nextAll() {
    return new vectorptr_messageelement(RobotRaconteurJavaJNI.WrappedGeneratorClient_nextAll(swigCPtr, this), true);
  }

}
