#include "stdafx.h"
#include "OrbiterCamera.h"
#include <cinder/CinderMath.h>
#include "LeapInteraction.h"

using namespace cinder;

const float MIN_CAMERA_DIST = 250.0f;
const float MAX_CAMERA_DIST = 350.0f;

const float MIN_FOV = 50.0f;
const float MAX_FOV = 90.0f;

OrbiterCamera::OrbiterCamera(float initialDistance) :
mTheta(100.0f), 
mPhi(0.0f),
mWheelZoom(0.0f), 
mCamDist(initialDistance),
mZoom(60.0f)
{
  mFovModifier.Update(0.0f, 0.0, 0.5f);
}

void OrbiterCamera::setFovModifier(float mod, double currentTime) {
  mFovModifier.Update(mod, currentTime, 0.95f);
}

void OrbiterCamera::onMouseMove(float dX, float dY) {
  mTheta -= dX;
  mPhi += dY;

  if (mTheta<0.f) mTheta += float(M_PI)*2.f;
  if (mTheta >= M_PI*2.f) mTheta -= float(M_PI)*2.f;
  mPhi = math<float>::clamp(mPhi, float(-M_PI)*0.45f, float(M_PI)*0.45f);

  // New camera update.
  util.RecordUserInput(dX, dY, 0.f);
}

void OrbiterCamera::onResize(float newAspectRatio) {
  setPerspective(80.0f + mFovModifier.value, newAspectRatio, 1.0f, 100000.f);
}

void OrbiterCamera::update(float dTheta, float dPhi, float dZoom) {
  mTheta -= dTheta;
  mPhi += dPhi;
  mZoom += dZoom;

  mZoom += mWheelZoom;
  mWheelZoom = 0.0f;

  if (mTheta<0.f) mTheta += float(M_PI)*2.f;
  if (mTheta >= M_PI*2.f) mTheta -= float(M_PI)*2.f;
  mPhi = math<float>::clamp(mPhi, float(-M_PI)*0.45f, float(M_PI)*0.45f);
  mZoom = math<float>::clamp(mZoom, 40.f, 110.f);

  const float blend = (mZoom - MIN_FOV) / (MAX_FOV - MIN_FOV);
  mCamDist = blend*(MAX_CAMERA_DIST - MIN_CAMERA_DIST) + MIN_CAMERA_DIST;

}
