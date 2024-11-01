---
title: Temporary Layer Input Processor
sidebar_label: Temporary Layer
---

## Overview

The temporary layer input processor is used to enable a layer when input events are received, and automatically disabling the layer when no further events are received in the given timeout duration. This most frequently is used to temporarily enable a layer with a set of [mouse button emulation behaviors](../behaviors/mouse-emulation.md#mouse-button-press) on it, so you can press various mouse buttons with the normal keyboard keys while using a physical pointer device for X/Y movement.

## Usage

When used, the temporary layer input processor takes two parameters, the layer index to enabled and a timeout value in milliseconds:

```dts
&zip_temp_layer 2 2000
```

which will enable the third layer and automatically disable it again after 2 seconds with no events from this pointing device.

## Pre-Defined Instances

Three pre-defined instance of the scaler input processor are available:

| Reference         | Description                                                     |
| ----------------- | --------------------------------------------------------------- |
| `&zip_temp_layer` | Enable a certain layer temporarily until no events are received |
