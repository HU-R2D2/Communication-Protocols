//! \addtogroup 0023 - ComminucationProtocols
//! \brief Defines different commincation protocols for embedded systems.
//!
//! ComminucationProtocol is a project to determine the different ways embedded systems can comminucate with each other.
//!
//! \file   ApplicationProtocol.hpp
//! \author Koen van der Kruk, 1654581
//! \date   Created: 16-6-2016
//! \date   Last Modified: 16-6-2016
//! \brief  ApplicationProtocol is used to define a type that other applications can use. Such as Qik and REST.
//!
//! ApplicationProtocol is used to define one way to talk to other applications with a TransportProtocol
//!
//! \copyright Copyright © 2016, HU University of Applied Sciences Utrecht.
//! All rights reserved.
//!
//! License: newBSD
//!
//! Redistribution and use in source and binary forms,
//! with or without modification, are permitted provided that
//! the following conditions are met:
//! - Redistributions of source code must retain the above copyright notice,
//!   this list of conditions and the following disclaimer.
//! - Redistributions in binary form must reproduce the above copyright notice,
//!   this list of conditions and the following disclaimer in the documentation
//!   and/or other materials provided with the distribution.
//! - Neither the name of the HU University of Applied Sciences Utrecht
//!   nor the names of its contributors may be used to endorse or promote
//!   products derived from this software without specific prior written
//!   permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//! "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
//! BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
//! AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//! IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
//! BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//! OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//! WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//! OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//! EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ~< HEADER_VERSION 2016 04 12 >~

#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#include "TransportProtocol.hpp"


/// An abstract class used to create a wrapper around a Applicaion Protocol.
/// \author Koen van der Kruk,
/// \version 1.0
/// \date 8-6-2016
class ApplicationProtocol{
public:

    /// Constructor to initialize a apllication protocol containing a transport protocol.
    /// \param t The transportprotocol used to transfer the data between multiple nodes
    ApplicationProtocol(TransportProtocol & t):transport{t}{};

    /// Can be used to change the TransportProtocol after the object is already initiliazed
    /// \param t The TransportProtocol used to transfer data between nodes.
    void setTransportProtocol(TransportProtocol & t){transport = t;};

protected:
    TransportProtocol & transport;
};

#endif
