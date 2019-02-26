// /d/shenlong/sea.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;
#include <ansi.h>
int do_practice(string arg);

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

void create()
{
        set("short","大海");
        set("long", @LONG
這是遼闊的海面，海風「呼呼」在你耳邊吹過，海浪一個接着一個
向你潑打過來，突然一個巨浪打來幾乎把你陷入旋渦中，你還是儘快離
開這兒吧。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "south" : __DIR__"beach",
        ]));
        set("outdoors", "shenlong");
        set("no_clean_up", 0);

        setup();
}

void init()
{
        add_action("do_practice", "practice");
        add_action("do_practice", "lian");
}

int do_practice(string arg)
{
        object *inv, weapon, me = this_player();
        string skillarg, str, multiple, skillname;
        int w, *cost, times, total, skill_special, skill_basic;
        mapping fam, skills, learned;

        skills = me->query_skills();
        learned = me->query_learned();
        skill_basic = me->query_skill(arg, 1);
        if( !stringp(skillname = me->query_skill_mapped(arg)) )
        {
                tell_object(me,"你必須有特殊武功方能與基本武技參照領悟！\n");
                return 1;
        }
        skill_special = me->query_skill(skillname, 1);

        if( skill_special < 1 )
        {
                tell_object(me,"你對這方面的技能還是一竅不通，最好從先從基本學起。\n");
                return 1;
        }        
        if( skill_basic > skill_special )
        {
                tell_object(me,"你" + to_chinese(skillname) + "功力不夠，無法繼續領悟" + to_chinese(arg) + "！\n");
                return 1;
        }
        skill_special=skill_special*query("max_jing", me)*2/(1000+query("max_jing", me));

        if( me->is_busy() )
        {
                tell_object(me, "你現在正忙着呢。\n");
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
                tell_object(me, "你還是先去跟師父多學習。\n");
                return 1;
        }
        if(!times || times == 0)
        {
                times = 1;
                multiple="";
        }
        else multiple="反覆";
        switch(skillarg) {
                case "blade" :
                case "club"  :
                case "staff" :
                case "stick" :
                case "sword" : 
                case "whip"  : str = "揮舞" + weapon->name(); break;
                case "cuff"  : str = "揮舞雙拳"; break;
                case "strike": str = "揮舞雙掌"; break;
                case "parry" : str = "奮力拚博"; break;
                case "dodge" : str = "縱閃跳躍"; break;
        }                
        message_vision("$N在海浪中" + str + multiple + "練習着" + to_chinese(skillarg) + "。\n", me);

        for(times; times > 0; times--)
        {
                cost = cost(me, skillarg);
                if( query("jing", me)<cost[0] || 
                         query("qi", me)<cost[1] )
                {
                        tell_object(me, "依你當前的狀況來看你不能如此練習。\n");
                        return 1;
                }
                me->receive_damage("qi", cost[1]);
                me->receive_damage("jing", random(skill_basic)/2,"冥思苦想把腦袋給想破了，白白的腦漿流了一地");
                me->improve_skill(skillarg, skill_special/8 + random(skill_special/4));

                total=query("jing", me)+query("qi", me);
                if( total < 500 && random(total) < 20 )
                {
                        message_vision("突然一個巨浪打來，$N陷入旋渦中，立即被海水吞沒了。\n", me);
                        for(int i = 0; i < sizeof(inv); i++)
                        {
                                if( userp(inv[i]) )
                                        inv[i]->receive_wound("qi",50+query("max_qi", inv[i]),"掉進海里淹死了");
                                else destruct(inv[i]);
                        }

                        me->unconcious();
                        me->move("/d/shenlong/beach");
                        message("vision","你發現一個渾身水淋淋的傢伙被海水衝上岸來，不由得走近一看，原來是"+me->name()+"\241\243\n", environment(me), ({me}));
                        return 1;
                }
        }
        
        return 1;
}

int *cost(object ob, string skill)
{
        if( query("potential", ob)>0 && query("neili", ob)>10 )
        {
                if( !random(3))addn("potential", -1, ob);
                else addn("neili", -8, ob);
                return ({0, 0});
        }
        else
        {
                switch(skill)
                {
                        case "blade" : return ({150, 300});
                        case "club"  : return ({200, 250});
                        case "staff" : return ({250, 200});
                        case "stick" : return ({300, 150});
                        case "sword" : return ({350, 100});
                        case "cuff"  : return ({350, 200});
                        case "strike": return ({200, 350});
                        case "parry" : return ({150, 250});
                        case "dodge" : return ({250, 150});
                }
        }
        return ({20, 20});
}
