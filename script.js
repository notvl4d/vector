let inputNrMuchii = document.getElementById("inputNrMuchii");
let inputMuchii = document.getElementById("inputMuchii");
let inputInterese =document.getElementById("inputInterese");
let output = document.getElementById("output");

let noduri,muchii,cost,x,y,nodStart,nrInterese,costSolutie=0,costMinim,lungimeSolutie;
let costuri=[],interese=[],vizitat=[],solutie=[];
function citire(){
    [noduri, muchii] = inputNrMuchii.value.trim().split(/\s+/).map(Number);
    for(let i=0;i<=noduri+3;i++){
        costuri[i] = [];
    }
    let muchiiInput = inputMuchii.value.trim().split("\n");
    for(let i=0;i<muchii;i++){
        let [x,y,cost] = muchiiInput[i].trim().split(" ").map(Number);
        costuri[x][y] = cost;
        costuri[y][x] = cost;
    }

    let intereseInput = inputInterese.value.trim().split(/\s+/);
    nrInterese = parseInt(intereseInput[0]);
    nodStart = parseInt(intereseInput[1]);
    for(let i=1;i<=nrInterese;i++){ 
        interese[i] = parseInt(intereseInput[i+1]);
    }
}

function ok(k){
    if(costuri[vizitat[k-1]][vizitat[k]]==0 && k>1)return 0;
    for(let i=1;i<k;i++)
        if(vizitat[i]==vizitat[k])
            return 0;
    return 1;
}

function verificareSolutie(k) {
    costSolutie=0;
    let freq = new Array(200).fill(false);
    for(let i = 1; i <= nrInterese; i++)
        freq[interese[i]] = true;
    for(let i = 1; i <= k; i++){
        if(freq[vizitat[i]] == 1) freq[vizitat[i]] = 0;
        if(i>1)
            costSolutie+=costuri[vizitat[i-1]][vizitat[i]];   
    }
    for(let i = 1; i <= 200; i++)
        if(freq[i] == 1) return 0;
    if(costuri[vizitat[k]][vizitat[1]] == 0) return 0; 
        costSolutie+=costuri[vizitat[k]][vizitat[1]];
    if(!costMinim)
        costMinim=costSolutie;
    else if(costSolutie<costMinim)
        costMinim=costSolutie;
    else return 0;
    return 1;
}

function Salvare(k)
{
    for(let i=1;i<=k;i++)
        solutie[i]=vizitat[i];
    lungimeSolutie=k;
}

function Back(k)
{
	for(let i=1; i<=noduri; i++)
	{
		vizitat[k]=i;
		if(ok(k))
			if(verificareSolutie(k))
				Salvare(k);
			else
				Back(k+1);
	}

}
function creereGraf(){

    const cy = cytoscape({
      container: document.getElementById('graf'),

      elements: [
      ],

      style: [
        {
          selector: 'node',
          style: {
            'label': 'data(id)',
            'background-color': '#4a90e2',
            'color': '#fff',
            'text-valign': 'center',
            'text-halign': 'center',
            'width': 40,
            'height': 40,
            'font-size': 14
          }
        },
        {
          selector: 'edge',
          style: {
            'width': 2,
            'line-color': '#888'
          }
        }
      ],
    });
    cy.container().style.width = '80vw';
    cy.container().style.height = '100vh';
    for(let i=1;i<=noduri;i++){
        cy.add({ data: { id: i.toString() } });
    }
    for(let i=1;i<=noduri;i++){
        for(let j=i+1;j<=noduri;j++){
            if(costuri[i][j]){
                cy.add({ data: { id: i.toString() + '-' + j.toString(), source: i.toString(), target: j.toString() } });
            }
        }
    }
    cy.layout({ name: 'cose', animate: true }).run();
}
function calculate(){
    output.innerHTML="";
    citire();
    creereGraf();
    vizitat[1] = nodStart;
    Back(2);
    for(let i=1;i<=lungimeSolutie;i++){
        output.innerHTML+=solutie[i]+"->";
    }
    output.innerHTML+=nodStart;
}


