
#include <ansi.h>
#include <buff.h>
#include <feature.h>

inherit CONDITION_MOD;

string id               = "battlefield_player_1";
string name     = HIW"永"NOR WHT"恆"HIW"榮"NOR WHT"耀"NOR;
string type     = CONDITION_TYPE_POSITIVE;
int time                = 86400;
int heartbeat   = 0;

// 啟動狀態時的效果
void start_effect(object ob)
{
        addn(query_key()+"/"+BUFF_STR, 8, ob);
        addn(query_key()+"/"+BUFF_PHY, 8, ob);
        addn(query_key()+"/"+BUFF_INT, 8, ob);
        addn(query_key()+"/"+BUFF_CHA, 8, ob);
        addn(query_key()+"/"+BUFF_AGI, 8, ob);
        addn(query_key()+"/"+BUFF_FOOD_MAX, 100, ob);
        addn(query_key()+"/"+BUFF_DRINK_MAX, 100, ob);
        addn(query_key()+"/"+BUFF_SOCIAL_EXP_BONUS, 15, ob);
        addn(query_key()+"/"+BUFF_COMBAT_EXP_BONUS, 15, ob);
        addn(query_key()+"/"+BUFF_STAMINA_MAX, 150, ob);
        addn(query_key()+"/"+BUFF_HEALTH_MAX, 150, ob);
        addn(query_key()+"/"+BUFF_ENERGY_MAX, 150, ob);

        ::start_effect(ob);
}

// 結束狀態時的效果
void stop_effect(object ob)
{
        ::stop_effect(ob);
}

// 狀態進行中的效果
void heart_beat_effect(object ob)
{


}

int stackable()
{
        return 3;
}
