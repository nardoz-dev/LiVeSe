
const tableBody = document.querySelector('tbody');

let out ="";
async function init(){
    var result = await fetch("https://42lal2bea7b5ufnq42umzkhxxy0zuhki.lambda-url.eu-west-1.on.aws/")
        .then ( data => {return data.json(); })
        .then ( data => {
            data.forEach(element => {
                out +=  ` 
                <tr>
                    <td> ${element.devEUI.S} </td>
                    <td> ${element.last_status.S} </td>
                    <td> ${element.lat.S} </td>
                    <td> ${element.long.S} </td>
                    <td> ${element.status.S} </td>
                    <td> ${element.street.S} </td>
                    <td> ${element.timestamp.S} </td>
                </tr>
                ` ;
            });
            tableBody.innerHTML = out;
        })

}
init();
