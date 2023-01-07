/////////////////////////////////////////////////////////////////////////////////////////
/// @file ObserverSubject.hpp
///
/// Observer design pattern interface.
///
/// @par Full Description.
/// Observer design pattern interface.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 04-March-2018 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2018 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined(OBSERVER_HPP)
#define OBSERVER_HPP

// SYSTEM INCLUDES
#include <vector>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
// <none>

// FORWARD REFERENCES
// <none>

namespace Observer {
/////////////////////////////////////////////////////////////////////////////
/// INTERFACE NAME: Observer
///
/// Provide interface for each observer.
///
/// @par Full Description
/// Provide interface for each observer concrete class.
/////////////////////////////////////////////////////////////////////////////
class ObserverIf
{
   public:
    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: Update
    //
    /// Fetching new data from Subject interface.
    ///
    /// @par Full Description
    /// Invoked by Subject. Fetching new data from Subject interface.
    /////////////////////////////////////////////////////////////////////////////
    virtual void Update() const = 0;
};

/////////////////////////////////////////////////////////////////////////////
/// INTERFACE NAME: ObserverSubject
///
/// Provide interface for each subject.
///
/// @par Full Description
/// Provide interface for each subject concrete class.
/////////////////////////////////////////////////////////////////////////////
class ObserverSubjectIf
{
   protected:
    std::vector<const ObserverIf *> m_ObserverClient;

   public:
    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: RegisterObserver
    //
    /// Observer register.
    ///
    /// @par Full Description
    /// Add observer to list of notified objects.
    ///
    /// @param rObserver An observer object.
    /////////////////////////////////////////////////////////////////////////////
    virtual void RegisterObserver(const ObserverIf & rObserver) = 0;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: RemoveObserver
    //
    /// Removing observer.
    ///
    /// @par Full Description
    /// Remove observer from  the list of notified objects.
    ///
    /// @return True if registration successful, false otherwise.
    /////////////////////////////////////////////////////////////////////////////
    virtual bool RemoveObserver(const ObserverIf & rObserver) = 0;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: Announce
    //
    /// Notify observers.
    ///
    /// @par Full Description
    /// Send to observer message that the state of object has changed.
    /////////////////////////////////////////////////////////////////////////////
    virtual void Announce() const = 0;
};
};  // namespace Observer

#endif /* OBSERVER_HPP */

/***************************************************************************
 *   Copyright (C) 2018 by Zbigniew Halat                                  *
 *   zby.halat@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/