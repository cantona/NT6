// quest_book.c 任務書籍

inherit ITEM;

void dest_me()
{
        object env;
        env=environment(this_object());
        if (objectp(env) && !env->is_character())
        destruct(this_object());
}
void dest_me1()
{
        destruct(this_object());
}

void create()
{
        set_name("本門秘籍", ({ "family book", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本線裝書，顏色有點老舊。\n");
                set("value", 0);
                set("material", "paper");
        }
//        call_out("dest_me",500);//500是任務時間
  call_out("dest_me1",1500);//1500是允許accept時間
}