/**
 * \file DecorCastle.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms castle decor in aquarium
 */
#pragma once
#include "Item.h"
#include<memory>
 /**
 * Class that forms castle decor in aquarium
 */
class CDecorCastle :
    public CItem
{
public:
    /// constructor
    CDecorCastle(CAquarium* aquarium);
    /// Default constructor (disabled)
    CDecorCastle() = delete;

    /// Copy constructor (disabled)
    CDecorCastle(const CDecorCastle&) = delete;
    /**
    *Save this item to an XML node
    * \param node The node we are going to be a child of
    * \return the node with its attribute type
    */
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

