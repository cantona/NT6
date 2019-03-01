//By rama@lxtx

inherit ITEM;

#include <ansi.h>

string *xc_msg1 =({
        "你神秘兮兮的四處張望xc_place的每個角落，",
        "你大模大樣在xc_place轉了幾個圈子，",
        "你滿臉嚴肅的仔細查看xc_place的情況，",
        "你仔細觀察了xc_place的情況，",
        "你在xc_place來回的巡查了幾遍，",
        "你細心留意xc_place上的陌生面孔，",
        "你向街上的人打探了xc_place近日的情況，",
        "你留意了下xc_place近來的變化，",
});
string *xc_msg2 = ({
        "據你的觀察來看，xc_place，",
        "以現在的情況來看，xc_place",
        "你覺得xc_place",
        "你默默在心裡記下---xc_place",
});

string *xc_msg3 = ({
        "沒有發現任何可疑之處。",
        "一切正常。",
        "沒有任何異常的跡象。",
        "一切太平。",
        "一切相安無事。",
});

string look_it(object me);
void create()
{
        set_name(HIG"巡城腰牌"NOR, ({ "yao pai","pai" }) );
        set_weight(600);
        if( clonep() )                 
        set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", (: look_it :) );
                set("value", 0);
             }   
}

void init()
{
        add_action("do_xunluo","xunluo");
}

int do_xunluo(object me, object ob)
{
        string the_place, msg1, msg2, msg3;
        mapping renwu;
        me=this_player();
        renwu=query("bang_quest", me);
        
        if( !mapp(renwu) )
                return 0;
        
        if( renwu["id"]!="xc")
                return 0;
        
        the_place = base_name(environment(this_player()));
        if (member_array(the_place,renwu["place"]) != -1)
        {
                msg1 = replace_string(xc_msg1[random(sizeof(xc_msg1))],"xc_place",the_place->short());
                msg2 = replace_string(xc_msg2[random(sizeof(xc_msg2))],"xc_place",the_place->short());
                msg3 = xc_msg3[random(sizeof(xc_msg3))];
                renwu["place"] -= ({ the_place });
                tell_object(me, msg1+msg2+msg3+"\n馬上去巡查下一個地方吧！\n");
        }
        else
                tell_object(me,"你沒必要在這裡巡邏啊！\n");
                
        return 1;
}

string look_it(object me)
{
        return "這是一塊"HIW"揚州小刀會"NOR"的巡城腰牌。"; 
}         