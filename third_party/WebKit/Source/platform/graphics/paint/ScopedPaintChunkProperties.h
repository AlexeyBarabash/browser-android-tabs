// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ScopedPaintChunkProperties_h
#define ScopedPaintChunkProperties_h

#include "platform/graphics/paint/DisplayItem.h"
#include "platform/graphics/paint/PaintChunk.h"
#include "platform/graphics/paint/PaintChunkProperties.h"
#include "platform/graphics/paint/PaintController.h"
#include "platform/wtf/Allocator.h"
#include "platform/wtf/Noncopyable.h"
#include "platform/wtf/Optional.h"

namespace blink {

class ScopedPaintChunkProperties {
  DISALLOW_NEW_EXCEPT_PLACEMENT_NEW();
  WTF_MAKE_NONCOPYABLE(ScopedPaintChunkProperties);

 public:
  // Use new PaintChunkProperties for the scope.
  ScopedPaintChunkProperties(
      PaintController& paint_controller,
      const PaintChunkProperties& properties,
      const DisplayItemClient& client,
      DisplayItem::Type type = DisplayItem::kUninitializedType)
      : paint_controller_(paint_controller),
        previous_properties_(paint_controller.CurrentPaintChunkProperties()) {
    paint_controller_.UpdateCurrentPaintChunkProperties(
        PaintChunk::Id(client, type), properties);
  }

  // Use new PropertyTreeState, and keep the current backface_hidden.
  ScopedPaintChunkProperties(
      PaintController& paint_controller,
      const PropertyTreeState& state,
      const DisplayItemClient& client,
      DisplayItem::Type type = DisplayItem::kUninitializedType)
      : paint_controller_(paint_controller),
        previous_properties_(paint_controller.CurrentPaintChunkProperties()) {
    PaintChunkProperties properties(state);
    properties.backface_hidden = previous_properties_.backface_hidden;
    paint_controller_.UpdateCurrentPaintChunkProperties(
        PaintChunk::Id(client, type), properties);
  }

  // Use new transform state, and keep the current other properties.
  ScopedPaintChunkProperties(
      PaintController& paint_controller,
      scoped_refptr<const TransformPaintPropertyNode> transform,
      const DisplayItemClient& client,
      DisplayItem::Type type = DisplayItem::kUninitializedType)
      : paint_controller_(paint_controller),
        previous_properties_(paint_controller.CurrentPaintChunkProperties()) {
    PaintChunkProperties properties(previous_properties_);
    properties.property_tree_state.SetTransform(std::move(transform));
    paint_controller_.UpdateCurrentPaintChunkProperties(
        PaintChunk::Id(client, type), properties);
  }

  // Use new clip state, and keep the current other properties.
  ScopedPaintChunkProperties(
      PaintController& paint_controller,
      scoped_refptr<const ClipPaintPropertyNode> clip,
      const DisplayItemClient& client,
      DisplayItem::Type type = DisplayItem::kUninitializedType)
      : paint_controller_(paint_controller),
        previous_properties_(paint_controller.CurrentPaintChunkProperties()) {
    PaintChunkProperties properties(previous_properties_);
    properties.property_tree_state.SetClip(std::move(clip));
    paint_controller_.UpdateCurrentPaintChunkProperties(
        PaintChunk::Id(client, type), properties);
  }

  // Use new effect state, and keep the current other properties.
  ScopedPaintChunkProperties(
      PaintController& paint_controller,
      scoped_refptr<const EffectPaintPropertyNode> effect,
      const DisplayItemClient& client,
      DisplayItem::Type type = DisplayItem::kUninitializedType)
      : paint_controller_(paint_controller),
        previous_properties_(paint_controller.CurrentPaintChunkProperties()) {
    PaintChunkProperties properties(previous_properties_);
    properties.property_tree_state.SetEffect(std::move(effect));
    paint_controller_.UpdateCurrentPaintChunkProperties(
        PaintChunk::Id(client, type), properties);
  }

  ~ScopedPaintChunkProperties() {
    // We should not return to the previous id, because that may cause a new
    // chunk to use the same id as that of the previous chunk before this
    // ScopedPaintChunkProperties. The painter should create another scope of
    // paint properties with new id, or the new chunk will use the id of the
    // first display item as its id.
    paint_controller_.UpdateCurrentPaintChunkProperties(WTF::nullopt,
                                                        previous_properties_);
  }

 private:
  PaintController& paint_controller_;
  PaintChunkProperties previous_properties_;
};

}  // namespace blink

#endif  // ScopedPaintChunkProperties_h
