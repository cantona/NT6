// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;

int do_suicide1(string arg);
int do_suicide2(string arg);
void create()
{
        set("short", "洞穴");
        set("long", @LONG
山巖下秘洞，曲折深邃，有如諸葛武侯之八卦迷陣一般，幽謎繁
復處尤有過之。越是深入越是陰濕黝暗，到後來竟已難見五指。洞穴
四面都是山，都是樹，雨後的山谷潮濕而新鮮，就像是個初浴的處女。
洞穴的四壁畫滿了圖畫，畫的卻不是人間，而是天上。
LONG
        );
        set("coor/x",2000);
        set("coor/y",-210);
        set("coor/z",0);
        set("no_magic",1);
        set("no_spells",1);
        set("no_fight",1);
        set("no_get_from",1);
        setup();
}

void init()
{
        add_action("do_suicide1", ({ "ci hou", "ci" }));
        add_action("do_suicide2", ({ "zhuang qiang", "zhuang" }));
}

int do_suicide1(string arg)
{
        object weapon;
        object me = this_player();

        weapon=query_temp("weapon", me);
        
        if (! weapon)
                return notify_fail("你沒有拿武器怎麼刺喉自殺？\n");

        tell_object(me, HIW "你回憶起以前的經歷，想想現在的處境，頓時心灰意冷，覺得已無意念繼續活下去。\n\n" NOR);
             
        message_vision(HIW "$N" HIW "拿起手中的" + weapon->name() + HIW "朝自己喉嚨刺去。\n" NOR, me);        
        message_vision("突然一條淡淡的影子，帶著種淡淡的香氣，從$N" 
                                   "面前飛了過去，瞬間奪下" + weapon->name() + "後消失不見。\n", me); 
        
        weapon->move("/d/yuanyue/gu5");
        
        tell_object(me, HIW "此時的你一心想自殺，連手中兵器被奪，也未去細想。\n" NOR);
        set_temp("mojiao/suicide", 1, me);
        return 1;
}

int do_suicide2(string arg)
{
        object me = this_player();
                
        if( !query_temp("mojiao/suicide", me) )
                return notify_fail("你想要幹什麼？\n");
                
        tell_object(me, HIW "你此時一心只想自殺，口中喃喃念道：沒有兵器我撞牆還不行嗎？！\n\n" NOR);
             
        message_vision(HIW "$N" HIW "騰空飛起將頭朝洞穴的牆壁直撞而去。\n" NOR, me);  
        
        message_vision(HIW "突然只聞一聲嬌呼“且慢”，一條身影飛馳而過將$N" HIW "的身體從空拉住，\n"
                           "卻不知為時已晚，$N" HIW "的頭部已經撞上洞穴的牆壁，頓時昏了過去。\n" NOR, me);  
                                 
        tell_room(environment(me),"說時遲，那時快，那條身影毫無停留將"+query("name", me)+
                                   "抱起，朝洞穴深處飛了過去，瞬間消失不見。\n", me); 
        
        me->unconcious(); 
        me->move("/d/yuanyue/gu5");
        me->revive();
        
        delete_temp("mojiao/suicide", me);
        return 1;
}
