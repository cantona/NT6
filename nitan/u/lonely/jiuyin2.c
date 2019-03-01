#include <ansi.h>

void create()
{
        seteuid(getuid());
}

object book = find_object("/clone/lonely/book/zhenjing2");

object get_owner()
{
        object owner;
        if(objectp(book)) {
                owner = environment(book);
                if(owner->is_character()) return owner;
        }
        return 0;
}

object book_owner = get_owner();
nosave string book_owner_name = objectp(book_owner)?query("name", book_owner):"某人";

string get_book()
{
        if(objectp(book)) destruct(book);
        if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
        return book_owner_name + "飛身去抓九陰真經~";
}

int do_rumor(string arg)
{
        CHANNEL_D->do_channel(this_object(), "rumor", arg);
        return 1;
}
nosave mixed *story = ({
        "陳玄風：你這兩天怎麼不好好練九陰白骨爪了？",
        "梅超風：你還說...你還說...你不愛我了！",
        "梅超風：你不知道，現在流行美甲?人家小姐說我的指甲成色不好,都是白骨爪練的。",
        "陳玄風：......",
        "陳玄風：那...那本真經呢？",
        "梅超風：我想想...哦上次做頭發的時候，隨便翻翻，忘記拿回來了。",
        "陳玄風口吐白沫，昏了過去。（臭婆娘....敗家子....）",
        (: do_rumor, "\"銅屍\" 陳玄風重出江湖..." :),
        book_owner_name + "，懸崖邊。",
        book_owner_name + "：逃到這應該找不到我了吧！！抓緊時間練功！",
        book_owner_name + "：恩，九陰真經果然厲害，可惜只有下本.......",
        "陳玄風：哼哼.........",
        book_owner_name + "：哇！鬼呀！！！",
        "陳玄風，" + book_owner_name + "：啊！九陰真經啊！！！！",
        (: get_book :),
        (: do_rumor, book_owner_name + "為了九陰真經不慎跌下懸崖，摔暈了。" :),
});

string prompt() { return HIW "【武林軼事】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
