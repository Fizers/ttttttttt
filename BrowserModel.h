#ifndef BROWSERMODEL_H
#define BROWSERMODEL_H
#include <memory>
#include "ModelInform.h"

class BrowserModel
{
public:
    BrowserModel() = default;
    virtual ~BrowserModel() = default;
    virtual void UpdateBrowser( QList<AllInf> inf) const = 0;
};
#endif // BROWSERMODEL_H
