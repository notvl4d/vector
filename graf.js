function creereGraf(){

    const cy = cytoscape({
      container: document.querySelector('.map-component'), 
        panningEnabled: false,
        userPanningEnabled: false,
        zoomingEnabled: false,
        userZoomingEnabled: false,

        elements: [
            { data: { id: '1' }, position: { x: 800, y: 200 } },
            { data: { id: '2' }, position: { x: 400, y: 150 } },
            { data: { id: '3' }, position: { x: 600, y: 300 } },
            { data: { id: '4' }, position: { x: 450, y: 500 } },
            { data: { id: '5' }, position: { x: 250, y: 450 } },
            { data: { id: '6' }, position: { x: 100, y: 300 } },

            {data: { id: '1-2', source: '1', target: '2' }},
            {data: { id: '2-3', source: '2', target: '3' }},    
            {data: { id: '3-4', source: '3', target: '4' }},
            {data: { id: '4-5', source: '4', target: '5' }},
            {data: { id: '5-6', source: '5', target: '6' }},
            {data: { id: '6-1', source: '6', target: '1' }},
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
            selector: '.rosu',
            style: {
                'background-color': 'red'
            }
        },
        {
          selector: 'edge',
          style: {
            'width': 2,
            'line-color': '#888'
          }
        },
        {
            selector: '.muchie',
            style: {
                'width': 3,
                'line-color': 'red',
                'target-arrow-shape': 'triangle',
                'target-arrow-color': 'red',
                'curve-style': 'bezier'  
            }
        }
      ],

      layout: { name: 'preset' }
    });
    cy.container()
    cy.container().style.width = '100%';
    cy.container().style.height = '100vh';
}
console.log("Creare graf...");
creereGraf();