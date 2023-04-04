#pragma once

#define DBG(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
