/*****************************************************************************\
* $Id: Crate.h,v 1.9 2010/02/04 10:43:24 paste Exp $
\*****************************************************************************/
#ifndef __EMU_FED_CRATE_H__
#define __EMU_FED_CRATE_H__

#include <vector>

#include "Exception.h"
#include "emu/fed/DDU.h"
#include "emu/fed/DCC.h"

namespace emu {
	namespace fed {

		class VMEController;

		/** @class Crate An object that contains VMEModules and a VMEController.  **/
		class Crate
		{
		public:

			/** Default constructor.
			*
			*	@param myNumber the identification number of the crate.
			**/
			Crate(const unsigned int &myNumber = 0)
			throw (emu::fed::exception::SoftwareException);

			/** Default destructor.**/
			~Crate();

			/** @returns the identification number of the crate. **/
			const unsigned int number() { return number_; }
			const unsigned int getNumber() { return number_; }

			/** Set the crate number **/
			inline void setNumber(const unsigned int &number) { number_ = number; }

			/** @returns true if the crate can be identified as a Track Finder crate, false otherwise. **/
			bool isTrackFinder();

			/** Adds a VMEModule to the crate. **/
			void addBoard(VMEModule *myBoard)
			throw (emu::fed::exception::OutOfBoundsException);

			/** Sets the VMEController in the crate. **/
			void setController(VMEController *controller)
			throw (emu::fed::exception::SoftwareException);

			/** @returns a pointer to the crate's VMEController. **/
			inline VMEController *getController() { return vmeController_; }

			/** @returns all the boards of type T that are in the crate. **/
			template<typename T>
			std::vector<T *> getBoards()
			{

				// Check to see if we have any boards to return.
				std::vector<T *> returnVector;
				for (std::vector<VMEModule *>::iterator iBoard = boardVector_.begin(); iBoard != boardVector_.end();  iBoard++) {
					T *board = dynamic_cast<T *>((*iBoard));
					if (board != 0) returnVector.push_back(board);
				}

				return returnVector;
			}

			/** @returns a vector of all the DDUs in the crate. **/
			inline std::vector<DDU *> getDDUs() { return getBoards<DDU>(); }

			/** @returns a vector of all the DCCs in the crate. **/
			inline std::vector<DCC *> getDCCs() { return getBoards<DCC>(); }

			/** @returns a pointer to the special broadcast DDU for the crate. **/
			inline DDU *getBroadcastDDU() { return broadcastDDU_; }

			//inline DCC *getBroadcastDCC() { return broadcastDCC_; }

			/** @returns the calculated RUI for the given DDU slot number in this crate. **/
			uint16_t getRUI(const int &slot);
			uint16_t getRUI(DDU *const myDDU) {
				return getRUI(myDDU->slot());
			}

			/** Relay the configure command to all the boards in the crate. **/
			void configure()
			throw (emu::fed::exception::ConfigurationException);

			/** Deletes the board from the crate and invalidates the given pointer. **/
			template<typename T>
			void deleteBoard(T *board)
			{
				for (std::vector<VMEModule *>::iterator iBoard = boardVector_.begin(); iBoard != boardVector_.end(); ++iBoard) {
					if (board == *iBoard) {
						boardVector_.erase(iBoard);
						return;
					}
				}
			}

		private:

			/// The unique identification number for the crate.
			unsigned int number_;

			/// The boards in the crate.
			std::vector<VMEModule *> boardVector_;

			/// A pointer to VMEController for the crate.
			VMEController *vmeController_;

			/// A pointer to the special broadcast DDU for the crate.
			DDU *broadcastDDU_;

		};

	}
}

#endif

