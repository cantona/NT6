//Obj: /d/ruzhou/npc/obj/xitie.c  喜貼，參加婚宴的請柬
// llm 99/07

inherit ITEM;

void create()
{
        set_name("喜帖", ({ "xi tie","tie"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else
   {
                set("unit", "張");
                set("long","一張大紅的帖子，上面寫著：\n"
                        "誠邀閣下參加我們的在汝州紅娘莊的婚禮和汝州迎賓樓的婚宴。\n");
      set("material", "paper");
        }
        setup();
}
