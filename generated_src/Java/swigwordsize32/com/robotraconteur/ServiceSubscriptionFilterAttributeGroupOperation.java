/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.robotraconteur;

public enum ServiceSubscriptionFilterAttributeGroupOperation {
  ServiceSubscriptionFilterAttributeGroupOperation_OR,
  ServiceSubscriptionFilterAttributeGroupOperation_AND,
  ServiceSubscriptionFilterAttributeGroupOperation_NOR,
  ServiceSubscriptionFilterAttributeGroupOperation_NAND;

  public final int swigValue() {
    return swigValue;
  }

  public static ServiceSubscriptionFilterAttributeGroupOperation swigToEnum(int swigValue) {
    ServiceSubscriptionFilterAttributeGroupOperation[] swigValues = ServiceSubscriptionFilterAttributeGroupOperation.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (ServiceSubscriptionFilterAttributeGroupOperation swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + ServiceSubscriptionFilterAttributeGroupOperation.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private ServiceSubscriptionFilterAttributeGroupOperation() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private ServiceSubscriptionFilterAttributeGroupOperation(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private ServiceSubscriptionFilterAttributeGroupOperation(ServiceSubscriptionFilterAttributeGroupOperation swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

