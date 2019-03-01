#include <ansi.h>
inherit ROOM;

string look_bi();
string look_pic1();
string look_pic2();
string look_pic3();

void create()
{
        set("short", "諸神仙洞內");
        set("long", @LONG
四周很空曠，偶爾說話也能聽見回聲，但這裡靠近洞口光線還算
不錯。千百年來的塵土已將周圍山壁(bi)掩蓋。
LONG );
        set("item_desc",([
               "bi" :  (: look_bi :),
               "pic1": (: look_pic1 :),
               "pic2": (: look_pic2 :),
               "pic3": (: look_pic3 :),
               
               
        ]));

        set("exits",([
               "out":__DIR__"outzhushendong",
        ]));        
                     
       setup();
}

string look_bi()
{
      object me = this_player();

      if( !query_temp("gua", me) )
          return NOR + WHT "塵土已將其掩蓋，不知道後面藏有什麼。你不禁想將塵土刮去看看"
                 "後面是什麼樣的。\n" NOR;
      
      return HIY "\n只見山壁上刻有三副巨圖。圖中人物個持寶劍，與人比武。\n"
             "第一副(pic1)的人物欲退反進，以守為攻。\n"
             "第二副(pic2)的人物手中之劍卻突然化為無數把攻向對手。\n"
             "第三副(pic3)更為奇怪，那人物卻突然一分為五，分使五種不同招式。\n"
             "你越看越奇怪，忍不住想跟著參悟起來。\n\n" NOR;
      
}

string look_pic1()
{
      object me = this_player();

      if( !query_temp("gua", me) )
          return NOR + WHT "這裡沒有你要看的東西。\n" NOR;

     return HIY "\n圖中人物以守為攻，欲退反進，攻其不備。\n" NOR;
}

string look_pic2()
{
      object me = this_player();

      if( !query_temp("gua", me) )
          return NOR + WHT "這裡沒有你要看的東西。\n" NOR;

     return HIY "\n圖中人物千劍齊發，令對手無從招架。\n" NOR;
}

string look_pic3()
{
      object me = this_player();

      if( !query_temp("gua", me) )
          return NOR + WHT "這裡沒有你要看的東西。\n" NOR;

     return HIY "\n圖中人物一分為五，分使五招，但見招招精妙，氣壓群山。\n" NOR;
}

void init()
{              
        add_action("do_canwu",({"canwu","think"}));
        add_action("do_gua", ({"gua"}));
        
}

int do_gua(string arg)
{
    object me = this_player();

    if (me->is_busy())
          return notify_fail("你現在正忙著呢。\n");

    if (me->is_fighting())
          return notify_fail("你在戰鬥哦？！小心，來了！！！\n");

    if (! arg || arg != "bi")
          return notify_fail("你要刮什麼？\n");

    write(HIG "\n你走到山壁旁，將山壁上的塵土一一刮去，後面景象一一顯露了出來。\n" NOR);
    set_temp("gua", 1, me);
   
    return 1;
    
}
int do_canwu(string msg)
{
    object me = this_player();

    string where, witch;
    
    if (! msg)return notify_fail("你要參悟什麼？\n");

    if (sscanf(msg, "%s from %s", witch, where) != 2)
          return notify_fail("你要參悟什麼？\n");

    if (me->is_busy())
          return notify_fail("你現在正忙著呢。\n");

    if (me->is_fighting())
          return notify_fail("你在戰鬥哦？！小心，來了！！！\n");

    if (witch != "pic1"
        && witch != "pic2"
        && witch != "pic3")
          return notify_fail("你想參悟什麼？\n");

    if (where != "bi")
          return notify_fail("這裡沒什麼給你參悟的啊！\n");

    if ((int)me->query_skill("martial-cognize", 1) < 220)
          return notify_fail("你的武學修養不夠，無法領悟石壁上的武功！\n");

    if ((int)me->query_skill("force", 1) < 180)
          return notify_fail("你的內功修為不夠，無法貫通石壁上的絕學！\n");

    if( query("max_neili", me)<3000 )
          return notify_fail("你的內力修為不足，無法貫通石壁上的絕學！\n");

    if( query("jing", me)<100 )
          return notify_fail("你的精力無法集中，無法領悟石壁上的絕學！\n");

    if (me->query_skill("wushen-jian", 1) < 180)
          return notify_fail("你對衡山五神劍所知實在有限，無法領悟石壁上的絕學！\n");

    if (witch == "pic1" 
         && query("can_perform/wushen-jian/hui", me) )
          return notify_fail("這項絕學你不是已經會了嗎？\n");

    else 
    if (witch == "pic2" 
         && query("can_perform/wushen-jian/qian", me) )
          return notify_fail("這項絕學你不是已經會了嗎？\n");

    else 
    if (witch == "pic3" 
         && query("can_perform/wushen-jian/shen", me) )
          return notify_fail("這項絕學你不是已經會了嗎？\n"); 

    me->receive_damage("jing", 95);

    me->start_busy(2 + random(4));

    if (random(2) == 1 && witch == "pic1")
    {
        addn("wushen_perform/hui/count", 1, me);

        if( query("wushen_perform/hui/count", me) >= 10 )
        {
            write(HIM "猛然間，你一聲長嘯，胸中豁然貫通，再無疑慮。\n" NOR);
            write(HIC "你終于通曉了絕學「回峰蜿蜒勢」。\n" NOR);

            set("can_perform/wushen-jian/hui", 1, me);
            delete("wushen_perform/hui/count", me);

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("wushen-jian"))
                    me->improve_skill("wushen-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "你對「回峰蜿蜒勢」這招有了新的認識，但是仍有許多不解之處。\n" NOR);
        me->start_busy(1 + random(2));
        return 1;   
    }

    else 
    if (random(4) == 1 && witch == "pic2")
    {
        addn("wushen_perform/qian/count", 1, me);

        if( query("wushen_perform/qian/count", me) >= 16 )
        {
            write(HIM "猛然間，你一聲長嘯，胸中豁然貫通，再無疑慮。\n" NOR);
            write(HIC "你終于通曉了絕學「千劍縱橫勢」。\n" NOR);

            set("can_perform/wushen-jian/qian", 1, me);
            delete("wushen_perform/qian/count", me);

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("wushen-jian"))
                    me->improve_skill("wushen-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "你對「千劍縱橫勢」這招有了新的認識，但是仍有許多不解之處。\n" NOR);
        me->start_busy(2 + random(3));
        return 1;   
    }

    else 
    if (random(5) == 1 && witch == "pic3")
    {
        addn("wushen_perform/shen/count", 1, me);

        if( query("wushen_perform/shen/count", me) >= 20 )
        {
            write(HIM "猛然間，你一聲長嘯，胸中豁然貫通，再無疑慮。\n" NOR);
            write(HIC "你終于通曉了絕學「五神朝元勢」。\n" NOR);

            set("can_perform/wushen-jian/shen", 1, me);
            delete("wushen_perform/shen/count", me);

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("wushen-jian"))
                    me->improve_skill("wushen-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "你對「五神朝元勢」這招有了新的認識，但是仍有許多不解之處。\n" NOR);                
        me->start_busy(2 + random(3));
        return 1;   
    }

    else return notify_fail("你試圖從石壁上研究有關「衡山五神劍」的內容，但卻沒什麼效果！\n");

}