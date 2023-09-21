/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.robotraconteur;

public class WrappedNodeInfo2 {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected WrappedNodeInfo2(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(WrappedNodeInfo2 obj) {
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
        RobotRaconteurJavaJNI.delete_WrappedNodeInfo2(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setNodeID(NodeID value) {
    RobotRaconteurJavaJNI.WrappedNodeInfo2_NodeID_set(swigCPtr, this, NodeID.getCPtr(value), value);
  }

  public NodeID getNodeID() {
    long cPtr = RobotRaconteurJavaJNI.WrappedNodeInfo2_NodeID_get(swigCPtr, this);
    return (cPtr == 0) ? null : new NodeID(cPtr, false);
  }

  public void setNodeName(String value) {
    RobotRaconteurJavaJNI.WrappedNodeInfo2_NodeName_set(swigCPtr, this, value);
  }

  public String getNodeName() {
    return RobotRaconteurJavaJNI.WrappedNodeInfo2_NodeName_get(swigCPtr, this);
  }

  public void setConnectionURL(vectorstring value) {
    RobotRaconteurJavaJNI.WrappedNodeInfo2_ConnectionURL_set(swigCPtr, this, vectorstring.getCPtr(value), value);
  }

  public vectorstring getConnectionURL() {
    long cPtr = RobotRaconteurJavaJNI.WrappedNodeInfo2_ConnectionURL_get(swigCPtr, this);
    return (cPtr == 0) ? null : new vectorstring(cPtr, false);
  }

  public WrappedNodeInfo2() {
    this(RobotRaconteurJavaJNI.new_WrappedNodeInfo2(), true);
  }

}
