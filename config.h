#define versionMajor 1
#define versionMinor 0

// SFML stuff

#define ANTIALIASING 8

// MKS to pixel conversion

#define pixelToMeter(val) (static_cast<float>(val) / 20)
#define meterToPixel(val) (val * 20)

// Box2D stuff

#define defVelocityIterations 6
#define defPositionIterations 2

// Coop Shooter stuff

#define lettersScaling 2.f

#define defaultVelocityMaxX 10
#define defaultVelocityMaxY 10
#define defaultJumpHeight 500
#define defaultMovement 1

#define playerVelocityMaxX defaultVelocityMaxX
#define playerVelocityMaxY defaultVelocityMaxY
#define playerJumpHeight defaultJumpHeight
#define playerMovement defaultMovement
