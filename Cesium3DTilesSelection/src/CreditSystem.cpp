#include "Cesium3DTilesSelection/CreditSystem.h"

#include <algorithm>

namespace Cesium3DTilesSelection {

Credit CreditSystem::createCredit(const std::string& html) {
  // if this credit already exists, return a Credit handle to it
  for (size_t id = 0; id < _credits.size(); ++id) {
    if (_credits[id].html == html) {
      return Credit(id);
    }
  }

  // this is a new credit so add it to _credits
  _credits.push_back({html, -1});

  // return a Credit handle to the newly created entry
  return Credit(_credits.size() - 1);
}

const std::string& CreditSystem::getHtml(Credit credit) const noexcept {
  if (credit.id < _credits.size()) {
    return _credits[credit.id].html;
  }
  return INVALID_CREDIT_MESSAGE;
}

void CreditSystem::addCreditToFrame(Credit credit) {
  // if this credit has already been added to the current frame, there's nothing
  // to do
  if (_credits[credit.id].lastFrameNumber == _currentFrameNumber) {
    return;
  }

  // add the credit to this frame
  _creditsToShowThisFrame.push_back(credit);

  // if the credit was shown last frame, remove it from
  // _creditsToNoLongerShowThisFrame since it will still be shown
  if (_credits[credit.id].lastFrameNumber == _currentFrameNumber - 1) {
    _creditsToNoLongerShowThisFrame.erase(
        std::remove(
            _creditsToNoLongerShowThisFrame.begin(),
            _creditsToNoLongerShowThisFrame.end(),
            credit),
        _creditsToNoLongerShowThisFrame.end());
  }

  // update the last frame this credit was shown
  _credits[credit.id].lastFrameNumber = _currentFrameNumber;
}

void CreditSystem::startNextFrame() noexcept {
  _creditsToNoLongerShowThisFrame.swap(_creditsToShowThisFrame);
  _creditsToShowThisFrame.clear();
  _currentFrameNumber++;
}
} // namespace Cesium3DTilesSelection
