// /d/shenlong/jushi.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;
#include <ansi.h>

string *practice_types = ({
        "blade",
        "club",
        "staff",
        "stick",
        "sword",
        "whip",
        "cuff",
        "strike",
        "parry",
        "dodge",
});
        
int *cost(object, string);
void dropoff(object);

void create()
{
        set("short", "巨石");
        set("long", @LONG
你站在懸崖上的巨石上，四周山風陣陣，你頭發凌亂。巨石搖搖晃
晃，你凝氣守中，雙足穩穩站定。環顧四周，一片寂靜，巨石底下是萬
丈深淵，似乎在此很適宜練功。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "southwest" : __DIR__"luanshi",
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        object me = this_player();
        int lvl = (int)me->query_skill("dodge", 1);

        if( interactive(me) && !random((int)me->query_skill("dodge", 1)) )
        {
                call_out("dropoff", 1, me);             
                return;
        }

        add_action("do_practice",  "practice");
        add_action("do_practice",  "lian");
        add_action("do_jump", "jump");
}

int do_practice(string arg)
{
        object weapon, me = this_player();
        string skillarg, str, multiple;
        int w, *cost, times;

        if( me->is_busy() )
        {
                tell_object(me, "你現在正忙著呢。\n");
                return 1;
        }

        if( me->is_fighting() )
        {
                tell_object(me, "你已經在戰鬥中了，學一點實戰經驗吧。\n");
                return 1;
        }

        if( !arg ) return ("/cmds/skill/enable")->main(me, arg);

        if(sscanf(arg, "%s %d", skillarg, times) != 2 )
                skillarg = arg;

        if( (w = member_array(skillarg, practice_types)) == -1 )
        {
                tell_object(me, "這項技能不能在這兒練習。\n");
                return 1;
        }

        if( w < 6 )
        {
                if( !objectp(weapon=query_temp("weapon", me)) )
                {
                        tell_object(me, "你沒有拿武器怎麼練習？\n");
                        return 1;
                }
                else
                        if( query("skill_type", weapon) != skillarg )
                        {
                                tell_object(me, "你手中的武器不適合練你想練習的技能。\n");
                                return 1;
                        }
        }
        if( (int)me->query_skill(skillarg, 1) < 30 )
        {
                tell_object(me, "你還是先去跟你師父多多學習。\n");
                return 1;
        }
        if( (int)me->query_skill(skillarg, 1) > 100 )
        {
                tell_object(me, "你已經不用在這兒化時間練習這項技能了。\n");
                return 1;
        }                
        if(!times || times == 0)
        {
                times = 1;
                multiple="";
        }
        else    multiple="反復";
        switch(skillarg)
        {
                case "blade" :
                case "club"  :
                case "staff" :
                case "stick" :
                case "sword" : 
                case "whip"  : str = "揮舞" + weapon->name();  break;
                case "cuff"  : str = "揮舞雙拳"; break;
                case "strike": str = "揮舞雙掌"; break;
                case "parry" : str = "奮力拚博"; break;
                case "dodge" : str = "縱閃跳躍"; break;
        }                
        message_vision("$N在狂風中" + str + multiple + "練習著" + to_chinese(skillarg) + "。\n", me);

        for(times; times > 0; times--)
        {
                cost = cost(me, skillarg);
                if( query("jing", me)<cost[0] || 
                        query("qi", me)<cost[1] )
                {
                        tell_object(me, "依你當前的狀況來看你不能如此練習。\n");
                        return 1;
                }
                me->receive_damage("jing", cost[0]);
                me->receive_damage("qi", cost[1]);             
                me->improve_skill(skillarg, random((int)me->query_int()));

                if( !random((int)me->query_skill("dodge", 1)) )
                {
                        dropoff(me);
                        return 1;
                }
        }
        return 1;
}

int do_jump(string arg)
{
        object *inv, me = this_player();
        int mydodge = me->query_skill("dodge", 1);

        if( !arg || arg != "down" )
                return notify_fail("你要幹什麼？\n");

        tell_object(me, "奮力一跳，身子隨即直落下去。\n");
        message("vision", me->name() + "奮力一跳，便直落海裡。\n", environment(me), ({me}));
      
        if( random(mydodge - 30 ) < 10 )
        {
                for(int i = 0; i < sizeof(inv); i++)
                        if( userp(inv[i]) )
                                inv[i]->receive_wound("qi",50+query("max_qi", inv[i]),"掉進海裡淹死了");
                        else    destruct(inv[i]);
                me->unconcious();
                me->move("/d/shenlong/beach");
                message("vision","你發現一個渾身水淋淋的家伙被海水沖上岸來，不由得走近一看，原來是" + me->name() + "\241\243\n", environment(me), ({me}));
                return 1;
        }

        me->move("/d/shenlong/sea");
        tell_object(me, "你一掙眼便發覺已站定在海水裡。\n");
        message("vision", "只見" + me->name() + "從高處跳了下來。\n", environment(me), ({me}));
        return 1;
}

void dropoff(object me)
{
        object *inv = all_inventory(me);

        tell_object(me, "巨石一晃你立足不穩掉下海裡了。\n");
        message("vision", me->name()+"失足掉了下去。\n",environment(me),({me}));
        for(int i = 0; i < sizeof(inv); i++)
                if( userp(inv[i]) )
                        inv[i]->receive_wound("qi",50+query("max_qi", inv[i]),"掉進海裡淹死了");
                else    destruct(inv[i]);

        me->move("/d/shenlong/sea");
        me->unconcious();
        me->move("/d/shenlong/beach");

        message("vision","你發現一個渾身水淋淋的家伙被海水沖上岸來，不由得走近一看，原來是" + me->name() + "\241\243\n", environment(me), ({me}));
}

int *cost(object ob, string skill)
{
        if( query("potential", ob)>0 && query("neili", ob)>10){
                if( !random(3) ) 
                addn("potential", -1, ob);
                else addn("neili", -5, ob);
                return ({0, 0});
        }
        else
        {
                switch(skill)
                {
                        case "blade" : return ({10, 25});
                        case "club"  : return ({15, 20});
                        case "staff" : return ({20, 15});
                        case "stick" : return ({25, 10});
                        case "sword" : return ({30,  5});
                        case "cuff"  : return ({30, 15});
                        case "strike": return ({15, 30});
                        case "parry" : return ({10, 20});
                        case "dodge" : return ({20, 10});
                }
        }
        return ({15, 15});
}
