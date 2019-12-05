// AppDelegate.m
@try {
    [[[KNFKotlinNativeFramework alloc] init] helloFromKotlin];
}
@catch (NSException *exception) {
    NSLog(@"Caught");
}
