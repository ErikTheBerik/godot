/*************************************************************************/
/*  godot_view.h                                                         */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
<<<<<<< HEAD
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
=======
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

<<<<<<< HEAD
#import <AVFoundation/AVFoundation.h>
#import <MediaPlayer/MediaPlayer.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
#import <UIKit/UIKit.h>

class String;

<<<<<<< HEAD
@protocol DisplayLayer;
@protocol GodotViewRendererProtocol;

@interface GodotView : UIView <UIKeyInput>

@property(assign, nonatomic) id<GodotViewRendererProtocol> renderer;

@property(assign, readonly, nonatomic) BOOL isActive;

=======
@class GodotView;
@protocol DisplayLayer;
@protocol GodotViewRendererProtocol;

@protocol GodotViewDelegate

- (BOOL)godotViewFinishedSetup:(GodotView *)view;

@end

@interface GodotView : UIView

@property(assign, nonatomic) id<GodotViewRendererProtocol> renderer;
@property(assign, nonatomic) id<GodotViewDelegate> delegate;

@property(assign, readonly, nonatomic) BOOL isActive;

@property(assign, nonatomic) BOOL useCADisplayLink;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
@property(strong, readonly, nonatomic) CALayer<DisplayLayer> *renderingLayer;
@property(assign, readonly, nonatomic) BOOL canRender;

@property(assign, nonatomic) NSTimeInterval renderingInterval;

<<<<<<< HEAD
- (CALayer<DisplayLayer> *)initializeRendering;
- (void)stopRendering;
- (void)startRendering;

- (BOOL)becomeFirstResponderWithString:(String)p_existing;

@property(nonatomic, assign) BOOL useCADisplayLink;

=======
- (CALayer<DisplayLayer> *)initializeRenderingForDriver:(NSString *)driverName;
- (void)stopRendering;
- (void)startRendering;

>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
@end
