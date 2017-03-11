//
//  Header.h
//
//  Created by wangshuo on 2017/3/11.
//  Copyright © 2017年 wangshuo. All rights reserved.
//

#ifndef Header_h
#define Header_h

#ifdef DEBUG
#define debugLog(...) NSLog(__VA_ARGS__)
#define debugMethod() NSLog(@"%s", __func__)
#else
#define debugLog(...)
#define debugMethod()
#endif

#define STR(key)            NSLocalizedString(key, nil)

#define PATH_OF_APP_HOME    NSHomeDirectory()
#define PATH_OF_TEMP        NSTemporaryDirectory()
#define PATH_OF_DOCUMENT    [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]


#define APP_VERSION         [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]

#define RGB(A, B, C)        [UIColor colorWithRed:A/255.0 green:B/255.0 blue:C/255.0 alpha:1.0]

//--- Variable
#define NAVBAR_HEIGHT (iOS_V7 ? 64 : 44) //导航条高度
#define LINEHEIGHT (1 / [UIScreen mainScreen].scale) //缩放比例
#define iOS_V9 ([[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0) //是否iOS8系统
#define iOS_V8 ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0) //是否iOS8系统
#define iOS_V7 ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0) //是否iOS7系统
#define iOS_V6 ([[[UIDevice currentDevice] systemVersion] floatValue] >= 6.0) //是否iOS6系统
#define iPhone5 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) : NO)
#define iPhone4 (ScreenHeight <= 480)
#define iPhone6  ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(750, 1334), [[UIScreen mainScreen] currentMode].size) : NO)
#define iPhone6plus ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? (CGSizeEqualToSize(CGSizeMake(1125, 2001), [[UIScreen mainScreen] currentMode].size) || CGSizeEqualToSize(CGSizeMake(1242, 2208), [[UIScreen mainScreen] currentMode].size)) : NO)

#define kAppDelegate ((AppDelegate*)[UIApplication sharedApplication].delegate)
#define kAppWindow [[[UIApplication sharedApplication] delegate] window]
//拨打电话
#define canTel ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"tel:"]])
#define tel(phoneNumber) ([[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"tel://%@", phoneNumber]]])
//发送短信
#define canSms                 ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"sms:"]])
#define sms(phoneNumber)       ([[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"sms://%@",phoneNumber]]])
//打开URL
#define canOpenURL(appScheme) ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:appScheme]])
#define openURL(appScheme) ([[UIApplication sharedApplication] openURL:[NSURL URLWithString:appScheme]])

#define StretchableImage(image) [image resizableImageWithCapInsets:UIEdgeInsetsMake(image.size.height / 2 - 1, image.size.width / 2 - 1, image.size.height / 2 - 1, image.size.width / 2 - 1) resizingMode:UIImageResizingModeStretch]

#define StretchableTimeImage(image) [image resizableImageWithCapInsets:UIEdgeInsetsMake(image.size.height  - 5, image.size.width - 10, 3, 6) resizingMode:UIImageResizingModeStretch]


#define LoadImage(imgName) [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:imgName ofType:nil]]
#define LoadXib(xibname) [[[NSBundle mainBundle] loadNibNamed:xibname owner:self options:nil] lastObject]
#define ImageColor(imgName) [UIColor colorWithPatternImage:LoadImage(imgName)]
#define RGBA(r, g, b, a) [UIColor colorWithRed:r / 255.0 green:g / 255.0 blue:b / 255.0 alpha:a] //颜色

//Methods
#define ISNULLOBJECT(obj) [obj isEqual:[NSNull null]] //是否空对象
//字符串、字典、数组是否有效
#define STRINGHASVALUE(str) (str && [str isKindOfClass:[NSString class]] && [str stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]].length > 0)
#define DICTIONARYHASVALUE(dic) (dic && [dic isKindOfClass:[NSDictionary class]] && [dic count] > 0)
#define ARRAYHASVALUE(array) (array && [array isKindOfClass:[NSArray class]] && [array count] > 0)



#ifndef weakify
#if DEBUG
#if __has_feature(objc_arc)
#define weakify(object) autoreleasepool{} __weak __typeof__(object) weak##_##object = object;
#else
#define weakify(object) autoreleasepool{} __block __typeof__(object) block##_##object = object;
#endif
#else
#if __has_feature(objc_arc)
#define weakify(object) try{} @finally{} {} __weak __typeof__(object) weak##_##object = object;
#else
#define weakify(object) try{} @finally{} {} __block __typeof__(object) block##_##object = object;
#endif
#endif
#endif

#ifndef strongify
#if DEBUG
#if __has_feature(objc_arc)
#define strongify(object) autoreleasepool{} __typeof__(object) object = weak##_##object;
#else
#define strongify(object) autoreleasepool{} __typeof__(object) object = block##_##object;
#endif
#else
#if __has_feature(objc_arc)
#define strongify(object) try{} @finally{} __typeof__(object) object = weak##_##object;
#else
#define strongify(object) try{} @finally{} __typeof__(object) object = block##_##object;
#endif
#endif
#endif


#define PasteString(string) [[UIPasteboard generalPasteboard] setString:string] //复制数据
#define PasteImage(image) [[UIPasteboard generalPasteboard] setImage:image] //复制图片

#define STRINGISNUMBER(str) ([[NSPredicate predicateWithFormat:@"SELF MATCHES '[0-9]+'"] evaluateWithObject:str])

// 判断手机号码是否正确
#define MOBILEPHONEISRIGHT(phoneStr) ([[NSPredicate predicateWithFormat:@"SELF MATCHES '^1[345678][0-9]{9}$'"] evaluateWithObject:phoneStr])

// 检查字符串是否为有效的email地址
#define EMAILISRIGHT(emailStr) ([[NSPredicate predicateWithFormat:@"SELF MATCHES '^([a-zA-Z0-9_\\.\\-])+\\@(([a-zA-Z0-9\\-])+\\.)+([a-zA-Z0-9]{2,4})+$'"] evaluateWithObject:emailStr])

// 检查字符串是否为英文字符串
#define ENWORDISRIGHT(word) ([[NSPredicate predicateWithFormat:@"SELF MATCHES '^([a-zA-Z])'"] evaluateWithObject:word])

// 检查字符串是否为数字字符串
#define NUMBERISRIGHT(word) ([[NSPredicate predicateWithFormat:@"SELF MATCHES '^([0-9\\n]+)'"] evaluateWithObject:word])

// 检查字符串是否为英文和数字组成的字符串
#define ENANDNUMISRIGHT(word) ([[NSPredicate predicateWithFormat:@"SELF MATCHES '^[A-Za-z0-9\\\\s\\n]+$'"] evaluateWithObject:word])

// 屏幕宽度
#define ScreenWidth [UIScreen mainScreen].bounds.size.width
// 屏幕高度
#define ScreenHeight [UIScreen mainScreen].bounds.size.height

// 缓存目录
#define kPATH_OF_CACHES         [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0]

// 无网络链接key
#define NetworkDisconnectedKey          @"NetworkDisconnectedKey"
// 无网络链接 自定义errorCode
#define NetworkDisconnectedErrorCode    -1009

// 滚动回收速度
#define ScrollVelocityValue             50

// cell 浅出动画时间
#define CellCATransitionDuration        0.08

#define ALERT(title,msg) \
if (STRINGHASVALUE(title) || STRINGHASVALUE(msg)) \
{ \
[[[UIAlertView alloc] initWithTitle:title \
message:msg \
delegate:nil \
cancelButtonTitle:@"确定" \
otherButtonTitles:nil,nil] show]; \
}

//区分开发和发布环境
#ifndef __OPTIMIZE__

#define NSLog(...) NSLog(__VA_ARGS__)

#else

#define NSLog(...) \
{              \
}

#endif

//区分模拟器和真机
#if TARGET_OS_IPHONE
//iPhone Device

#endif

#if TARGET_IPHONE_SIMULATOR
//iPhone Simulator

#endif


#endif /* Header_h */
