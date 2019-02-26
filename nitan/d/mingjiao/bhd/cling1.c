// /d/mingjiao/bhd/congling1.c
// Jay 4/3/97 -qingyun
// Modify By River@SJ 99.06
#include <ansi.h>
#include <room.h>
inherit ROOM;
string look_tree();
void create()
{ 
        set("short",HIG"叢林"NOR);
        set("long", @LONG
這是一片厚厚的叢林。幾十丈高的樹木(tree)簇在一塊，密實的
枝葉象一蓬蓬巨傘恆伸向天空，把陽光遮得絲毫也無。由於叢林歷時
年代很久，又罕有人至，所以動植物種類很多，飛禽走獸應有盡有。
偶爾會有吃肉獸出來傷人。你一走進這這覺得陰陰森林的。
LONG );
        set("exits", ([
                "south" : __DIR__"cling",
        ]));    
        set("item_desc", ([
                "tree" : (: look_tree :),
          ]));
        set("objects",([
                "/d/mingjiao/npc/xiong"  :  2,
        ]));
        set("tree_count", 2);
        set("outdoors","冰火島");
        setup();
}

void reset()
{
        set("tree_count", 2);
        ::reset();
}

void init()
{
        add_action("do_chop","chop");
        add_action("do_chop","砍");
}

int do_chop(string arg)
{
        object me, weapon;
        me = this_player();
        weapon = me->query_temp("weapon");
        if( arg=="tree" || arg=="Tree" || arg=="樹木" ) {
             if(me->is_busy()) return notify_fail("你正忙着呢。\n");
             if(query("tree_count") < 1) return notify_fail("剩下的樹木都太大了，你還是再找找吧。\n");
             me->start_busy(1);
             if(!weapon){
                     message_vision("\n$N運功吐氣，一掌打在那千年老樹堅實的樹幹上，痛得$P眼淚直往下掉！\n\n",me);
                     me->set_temp("last_damage_from", "被自己的反震力打");
                     me->receive_wound("qi", 50);
                     me->receive_damage("qi", 50);
                     EMOTE_D->do_emote(me,"nocry");
                     return 1;
             }
             else if(weapon->query("flag")!=4){
                     message_vision("\n$N拿起$n，往樹上一陣亂敲。\n"+
                                    "結果梆的一聲掉下根枯樹枝來，正好打在$P頭上，頓時起了個大包！\n",me, weapon);
                     me->set_temp("last_damage_from", "被樹枝壓");
                     EMOTE_D->do_emote(me,"pain");
                     EMOTE_D->do_emote(me,"cry");
                     me->receive_wound("qi", 50);
                     me->receive_damage("qi", 50);
                     return 1;
             }
             else{
                     message_vision("\n$N操起$n，往樹幹上砍啊，砍啊，砍啊。。。\n",me, weapon);
                     if(random(100) > 90){
                          message_vision("\n只聽嘩啦一聲，這棵樹木總算被$N砍倒了。\n",me);
                          new("/d/mingjiao/obj/tree")->move(this_object());
                          add("tree_count", -1);
                     }
                     me->receive_damage("jing", random(20)+10);
                     me->improve_skill(weapon->query("skill_type"), random(me->query("str")));
                     return 1;
             }
        }
}    
   
string look_tree()
{
       return
       " 
                            m
           *               m*m
         *****            m***m
        ***|*/*          m*****m
       ****|****        mm*****mm
         **Y**          mm**Y**mm
^^    ^^   |   ^^  ^^      *|*     ^^   ^^
------------------------------------------

這裏的樹木高大茂密，樹幹結實，很適合製造船舶。\n";
}

