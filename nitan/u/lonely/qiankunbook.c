#include <ansi.h>

object book = find_object("/clone/book/qiankun_book");

object get_owner()
{
        object owner;
        if(objectp(book)) {
                owner = environment(book);
                if( !objectp(owner) ) return 0;
                if(owner->is_character()) return owner;
        }
        return 0;
}

object book_owner = get_owner();

string get_book()
{
        if(objectp(book)) destruct(book);
        if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
        return "張無忌：...............去死吧！";
}

nosave string book_owner_name = objectp(book_owner)?query("name", book_owner):"某人";

nosave mixed *story = ({
        "明教護教使者：報……，聽説乾坤心法被外人偷走了……。",
        "張無忌：咦……他奶奶的，敢到我明教偷東西，得好好找找！",
        "明教上下開始全面尋找此物......",
        "張無忌道：怎麼找不到了呢？有誰看到是誰偷的了麼？",
        "明教護教使者：報……好像是給" + book_owner_name + "偷去了。",
        "張無忌道：靠！怎麼不早説？我現在下山就去找他",
        "張無忌來到" + book_owner_name + "面前。",
        book_owner_name + "拔腿想跑，可被逮了個正着。",
                "張無忌：%—*（）（—……*—%￥###￥*（）（%*",
                "張無忌：你這小子！居然敢偷我明教的乾坤心法。",
        "張無忌使出九陽乾坤無上心法，" + book_owner_name + "頓時被嚇的半死！",
        book_owner_name + "：切！不就是乾坤心法麼，大不了還給你。",
        book_owner_name + "掏出羊皮書丟給張無忌。",
        (: get_book :),
        book_owner_name + "被張無忌打暈了。",
        "張無忌開開心心的回到明教。",
});

string prompt() { return HIW "【武林軼事】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
