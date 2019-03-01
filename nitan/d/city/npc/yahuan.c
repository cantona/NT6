// yahuan.c 丫鬟

inherit NPC;
void create()
{
        set_name( "丫鬟", ({ "ya huan", "yahuan" }) );
        set( "title", "楊府" );
        set( "attribute", "peaceful" );
        set( "gender", "女性" );
        set( "age", 15 );
        set( "long", @LONG
一個丫鬟，長的小巧可愛，圓圓的臉上帶笑看著你。
LONG);

        set( "str", 20 );
        set( "dex", 20 );
        set( "per", 22 );
        set( "combat_exp", 1000 );

        set( "inquiry", ([
                "楊府" : "嘻嘻，你不正在楊府嗎？\n",
                "小玲瓏山館" : "就是楊府。\n",
                "揚州" : "揚州繁華甲天下！\n",
                "楊磊石" : "那是我家少爺。\n"
        ]) );

        set("chat_chance", 20);
        set("chat_msg", ({
                "老爺說過不能隨便和陌生人搭腔的。\n",
                "小女子有事，對不起了。\n",
        }) );
        setup();
        carry_object(__DIR__"obj/pink_cloth" )->wear();
        carry_object(__DIR__"obj/flower_shoe" )->wear();
}