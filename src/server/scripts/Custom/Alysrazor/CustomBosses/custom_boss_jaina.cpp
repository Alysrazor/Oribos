/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ObjectAccessor.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "Unit.h"

struct custom_boss_jaina : public WorldBossAI
{
    enum JainaSays
    {
        SAY_JAINA_AGGRO = 0,
    };

    enum JainaSpells
    {
        SPELL_FROSTBOLT         = 116,
        SPELL_BLIZZARD          = 190356,
        SPELL_ICE_BLOCK         = 287322,
        SPELL_AVALANCHE         = 287565,
        SPELL_FREEZING_BLAST    = 287565,
    };

    enum JainaEvents
    {
        EVENT_FROSTBOLT = 1,
        EVENT_BLIZZARD,
        EVENT_ICE_BLOCK,
        EVENT_AVALANCHE,
        EVENT_FREEZING_BLAST
    };

    enum JainaPhases : uint8
    {
        PHASE_ONE = 1,
        INTERPHASE,
        PHASE_TWO,
    };

    void Reset() override
    {
        _Reset();
    }

    void JustEngagedWith(Unit* who) override
    {
        if (who->GetTypeId() == TYPEID_PLAYER)
            Talk(SAY_JAINA_AGGRO);

        events.SetPhase(PHASE_ONE);

        SchedulePhaseOneEvents();
        events.ScheduleEvent(EVENT_FROSTBOLT, Seconds(3));
    }

private:
    void SchedulePhaseOneEvents()
    {
        events.ScheduleEvent(EVENT_FREEZING_BLAST, Seconds(12), 0, PHASE_ONE);
    }

    
};





void AddSC_custom_boss_jaina()
{
    RegisterCreatureAI(custom_boss_jaina);
}
