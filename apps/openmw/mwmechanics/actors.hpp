#ifndef GAME_MWMECHANICS_ACTORS_H
#define GAME_MWMECHANICS_ACTORS_H

#include <set>
#include <vector>
#include <string>
#include <map>

#include "character.hpp"
#include "movement.hpp"
#include "../mwbase/world.hpp"

namespace Ogre
{
    class Vector3;
}

namespace MWWorld
{
    class Ptr;
    class CellStore;
}

namespace MWMechanics
{
    class Actors
    {
            typedef std::map<MWWorld::Ptr,CharacterController*> PtrControllerMap;
            PtrControllerMap mActors;

            std::map<std::string, int> mDeathCount;

            void updateNpc(const MWWorld::Ptr &ptr, float duration, bool paused);

            void adjustMagicEffects (const MWWorld::Ptr& creature);

            void calculateDynamicStats (const MWWorld::Ptr& ptr);

            void calculateCreatureStatModifiers (const MWWorld::Ptr& ptr, float duration);
            void calculateNpcStatModifiers (const MWWorld::Ptr& ptr);

            void calculateRestoration (const MWWorld::Ptr& ptr, float duration);

            void updateDrowning (const MWWorld::Ptr& ptr, float duration);

            void updateEquippedLight (const MWWorld::Ptr& ptr, float duration);

        public:

            Actors();
            ~Actors();

            /// Update magic effects for an actor. Usually done automatically once per frame, but if we're currently
            /// paused we may want to do it manually (after equipping permanent enchantment)
            void updateMagicEffects (const MWWorld::Ptr& ptr) { adjustMagicEffects(ptr); }

            void addActor (const MWWorld::Ptr& ptr);
            ///< Register an actor for stats management
            ///
            /// \note Dead actors are ignored.

            void removeActor (const MWWorld::Ptr& ptr);
            ///< Deregister an actor for stats management
            ///
            /// \note Ignored, if \a ptr is not a registered actor.

            void updateActor(const MWWorld::Ptr &old, const MWWorld::Ptr& ptr);
            ///< Updates an actor with a new Ptr

            void dropActors (const MWWorld::CellStore *cellStore, const MWWorld::Ptr& ignore);
            ///< Deregister all actors (except for \a ignore) in the given cell.

            void update (float duration, bool paused);
            ///< Update actor stats and store desired velocity vectors in \a movement

            void updateActor (const MWWorld::Ptr& ptr, float duration);
            ///< This function is normally called automatically during the update process, but it can
            /// also be called explicitly at any time to force an update.

            void restoreDynamicStats();
            ///< If the player is sleeping, this should be called every hour.
            
            int countDeaths (const std::string& id) const;
            ///< Return the number of deaths for actors with the given ID.

        void forceStateUpdate(const MWWorld::Ptr &ptr);

        void playAnimationGroup(const MWWorld::Ptr& ptr, const std::string& groupName, int mode, int number);
        void skipAnimation(const MWWorld::Ptr& ptr);
        bool checkAnimationPlaying(const MWWorld::Ptr& ptr, const std::string& groupName);
    };
}

#endif
