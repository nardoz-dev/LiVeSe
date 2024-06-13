// Table Variable
const tableBody = document.querySelector('tbody');
// Status Variable
let _status = ""


async function fetchData() {
    try {
        const response = await fetch("https://loreaqofqdepqcqo2fxd34fody0axwkn.lambda-url.eu-west-1.on.aws/");
        if (!response.ok) {
            throw new Error('Error during the retrieving of the data');
        }
        console.log("Retrieving data : Done")
        return await response.json();
    } catch (error) {
        console.error('Error during the retrieving of the data:', error);
        return [];
    }
}

async function displayData() {
    const data = await fetchData();
    let output = "";
    data.forEach(element => {
        output += ` 
            <tr>
                <td>${element._devEUI.S}</td>
                <td>${element.LastStatus.S}</td>
                <td>${element.Status.S}</td>
                <td>${element.Street.S}</td>
                <td>${element.TimeStamp.S}</td>
            </tr>`;
        
        if ( element.devEUI.S == "4" ){
            _status = element.Status.S
            console.log("_status dopo il displayData : ", _status)
        }
        
    });
    tableBody.innerHTML = output;
   
}

async function main (){
    // As First operation retrieve data : 
    await displayData()
  
    setInterval(async () => {
        currentIndex = (currentIndex + 1) % statusArray.length;
        await displayData()
    }, 10000); 

}

main()
