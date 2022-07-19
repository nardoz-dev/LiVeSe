

async function init(){
    var result = await fetch("https://42lal2bea7b5ufnq42umzkhxxy0zuhki.lambda-url.eu-west-1.on.aws/")
        .then ( data => {return data.json(); })
        .then ( data => {
            data.forEach(element => {
                console.log(element);
            });
        })

}


init();