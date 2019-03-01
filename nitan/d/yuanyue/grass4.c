// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "白梅園"); 
        set("long", @LONG
這裡便是白梅園了，平常金獅就最喜歡到這裡走走，說是在清雅
的梅香中能靜下心想些事情，每逢此時，銀龍定會撇撇下嘴，不屑道：
一個人的身上穿的若還是春天的薄衣服，肚子裡裝的若還是昨天吃的
陽春面，他唯一還有心情欣賞的東西就是可以往嘴裡吞下去、塞飽肚
子的，決不會是什麼梅花。當然梅花若是換成辣椒那倒可以考慮考慮。
秋天的梅樹上沒什麼花，但奇怪的是這裡仍飄散著一股清香。
LONG );
        set("type","forest");
        set("outdoors", "wansong");
        set("exits",([
                "east":__DIR__"woshi1",
                "west":__DIR__"woshi",
                "north":__DIR__"chaifang",
        ]) );
        set("item_desc", ([
                "梅樹": "梅樹上沒有花，樹幹上釘了一塊小牌子，年代看來很久遠了。\n",
                "tree": "梅樹上沒有花，樹幹上釘了一塊小牌子，年代看來很久遠了。\n",
                "牌子": "牌子上寫著-[..動埋....處。]，但是年代久遠，有幾個字看不清了。\n",
                "paizi": "牌子上寫著-[..動埋....處。]，但是年代久遠，有幾個字看不清了。\n"
        ]) );
        set("objects",([
                CLASS_D("mojiao/jinshi") : 1,
        ]) );
        
        set("coor/x",-590);
        set("coor/y",250);
        set("coor/z",80);
        setup();
} 

int dig_notify(object obj, int i)
{
        object me,jt;
        int qi;
        int max_qi;
        me = this_player();
        
        qi=query("qi", me);
        max_qi=query("max_qi", me);
        if (qi < max_qi/4) {
                message_vision("$N掄手中的"+obj->name()+"，但是腦中突然一陣眩暈......\n" , me);
           me->unconcious();
        }
        else {
                message_vision("$N手中的"+obj->name()+"碰到堅硬的地面，發出′叮′的一聲。\n" , me);
                me->receive_damage("qi",query("max_qi", me)/4);
                if (query("digged")) 
                {
                        message_vision("$N辛辛苦苦挖了半天什麼也沒挖到。\n", me);
                        return 1;
                }
                else
                {
                        switch ( random(3) )
                        {
                          case 0: 
                                message_vision("$N發現地下似乎有個酒壇子。\n",this_player());
                                jt = new(__DIR__"obj/bottle");
                                jt->move(this_player());
                                set("digged",1);
                                message_vision("$N激動地扔掉"+obj->name()+"，連忙撿起"+jt->name()+"。 \n",this_player());
                                destruct(obj);
                                break;
                          case 1:
                                message_vision("地上的土被$N翻起一塊,沒什麼發現。\n",obj);
                                break;
                          case 2:
                                message_vision("鏘．．得一聲，$N手中的"+obj->name()+"斷了。\n",this_player());
                                destruct(obj);
                                break;
                        }
                 }
                 me->start_busy(3);
         }
         return 1; 
}    
